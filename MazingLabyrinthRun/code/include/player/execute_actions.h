#ifndef PLAYER_EXECUTE_ACTION_HEADER_H
#define PLAYER_EXECUTE_ACTION_HEADER_H
#include "../include/entityBase/logic/movable_logic/move_sprite_event_decorator/moving_sprite_event_decorator.h"
#include "action.h"

#include <SFML/Graphics/Sprite.hpp>
#include <functional>
#include <memory>

class PlayerAction : public Action {
public:
	PlayerAction(PlayerState* state, sf::Sprite* sprite) : Action(sprite), m_state{state} {};
	virtual void apply() override = 0;

protected:
	PlayerState* m_state;
};

class JumpAction : public PlayerAction {
public:
	JumpAction(PlayerState* state, sf::Sprite* sprite) : PlayerAction(state, sprite){};
	void apply() override { m_state->currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_JUMP; }
};

class RunAction : public PlayerAction {
public:
	RunAction(PlayerState* state, sf::Sprite* sprite) : PlayerAction(state, sprite){};
	void apply() override { m_state->currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_RUN; }
};

class IdleAction : public PlayerAction {
public:
	IdleAction(PlayerState* state, sf::Sprite* sprite) : PlayerAction(state, sprite){};
	void apply() override { m_state->currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_STATIONARY; }
};

inline std::vector<std::unique_ptr<Action>>
    get_action_list(sf::Sprite* sprite, PlayerState* state, const std::vector<ActionList>& action_name_list) {
	std::vector<std::unique_ptr<Action>> actions_list;

	for (const auto& action_name : action_name_list) {
		if (action_name == ActionList::move_right) actions_list.push_back(std::make_unique<MoveRight>(state, sprite));
		if (action_name == ActionList::move_left) actions_list.push_back(std::make_unique<MoveLeft>(state, sprite));
		if (action_name == ActionList::move_up) actions_list.push_back(std::make_unique<MoveUp>(state, sprite));
		if (action_name == ActionList::move_down) actions_list.push_back(std::make_unique<MoveDown>(state, sprite));

		if (action_name == ActionList::move_down || action_name == ActionList::move_left ||
		    action_name == ActionList::move_up || action_name == ActionList::move_right)
			actions_list.push_back(std::make_unique<RunAction>(state, sprite));

		if (action_name == ActionList::jump) actions_list.push_back(std::make_unique<JumpAction>(state, sprite));
		if (action_name == ActionList::idle) actions_list.push_back(std::make_unique<IdleAction>(state, sprite));
	}

	return actions_list;
}

#endif