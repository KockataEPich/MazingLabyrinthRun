#ifndef PLAYER_ACTIONS_HEADER_H
#define PLAYER_ACTIONS_HEADER_H
#include "../include/entityBase/logic/movable_logic/move_actions.h"
#include <functional>
#include <memory>

class JumpAction : public ActionUsingState<PlayerState> {
public:
	JumpAction(sf::Sprite* sprite, PlayerState* state) : ActionUsingState<PlayerState>(sprite, state){};
	void apply_action() override { m_state->action_type = ActionType::jump; }
};

#endif