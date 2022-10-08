#ifndef PLAYER_PLAYER_ACTIONS_HEADER_H
#define PLAYER_PLAYER_ACTIONS_HEADER_H
#include "../include/entityBase/logic/movable_logic/move_actions.h"

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
	void apply() override { m_state->current_animation = AnimationType::MAIN_CHARACTER_DEFAULT_JUMP; }
};

class RunAction : public PlayerAction {
public:
	RunAction(PlayerState* state, sf::Sprite* sprite) : PlayerAction(state, sprite){};
	void apply() override { m_state->current_animation = AnimationType::MAIN_CHARACTER_DEFAULT_RUN; }
};

class IdleAction : public PlayerAction {
public:
	IdleAction(PlayerState* state, sf::Sprite* sprite) : PlayerAction(state, sprite){};
	void apply() override { m_state->current_animation = AnimationType::MAIN_CHARACTER_DEFAULT_STATIONARY; }
};

#endif