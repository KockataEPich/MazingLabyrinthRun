#ifndef PLAYER_ACTIONS_HEADER_H
#define PLAYER_ACTIONS_HEADER_H
#include "../include/entityBase/logic/movable_logic/move_actions.h"
#include <functional>
#include <memory>

class JumpAction : public EventUsingState<PlayerState> {
public:
	JumpAction(sf::Sprite* sprite, PlayerState* state) : EventUsingState<PlayerState>(sprite, state){};
	void event() override { m_state->action_type = ActionType::jump; }
};

#endif