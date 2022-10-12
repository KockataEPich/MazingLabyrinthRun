#ifndef SPRITE_ACTION_HEADER
#define SPRITE_ACTION_HEADER

#include <SFML/Graphics/Sprite.hpp>
#include <list>
#include <memory>

class Action {
public:
	Action(sf::Sprite* sprite) : m_sprite{sprite} {}
	void apply() {
		before_applying();
		apply_action();
		after_applying();
	}
	virtual void apply_action() = 0;

	virtual void before_applying(){};
	virtual void after_applying(){};

	bool is_finished() { return m_finished; }

protected:
	sf::Sprite* m_sprite;
	bool m_finished = true;
};

template<typename T>
class ActionUsingState : public Action {
public:
	ActionUsingState(sf::Sprite* sprite, T* state) : Action(sprite), m_state{state} {};

protected:
	T* m_state;
};

class CompositeAction : public Action {
public:
	void add_action(std::unique_ptr<Action>&& action) { m_actions.push_back(std::move(action)); }

protected:
	std::list<std::unique_ptr<Action>> m_actions;
};

class ParallelActions : public CompositeAction {
public:
	void apply_action() override {
		for (auto& action : m_actions) action->apply();
		m_actions.remove_if([](std::unique_ptr<Action>& action) { return action->is_finished(); });
		m_finished = m_actions.empty();
	}
};

class SequenceActions : CompositeAction {
public:
	void apply_action() override {
		if (!m_actions.empty()) {
			m_actions.front()->apply();
			if (m_actions.front()->is_finished()) m_actions.pop_front();
		}
		m_finished = m_actions.empty();
	}
};

#endif