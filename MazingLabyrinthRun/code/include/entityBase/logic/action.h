#ifndef SPRITE_ACTION_HEADER
#define SPRITE_ACTION_HEADER

#include <SFML/Graphics/Sprite.hpp>
class Action {
public:
	Action(sf::Sprite* sprite) : m_sprite{sprite}{}
	void apply() {
		before_applying();
		apply_action();
		after_applying();
	}
	virtual void apply_action() = 0;

	virtual void before_applying(){};
	virtual void after_applying(){};

	bool is_finished() {return m_finished;}
protected:
	sf::Sprite* m_sprite;
	bool m_finished = true;
};

template<typename T>
class ActionUsingState : public Action{
public:
	ActionUsingState(sf::Sprite* sprite, T* state) : Action(sprite), m_state{state}{};
protected:
	T* m_state;
};

#endif