#ifndef ACTIVE_OBJECT_STATE_HEADER_H
#define ACTIVE_OBJECT_STATE_HEADER_H

#include "../../attribute/action_type.h"
#include "../logic/action.h"

struct ActiveObjectState {
	float delta_time;
	ActionType action_type;
};

class IdleAction : public ActionUsingState<ActiveObjectState> {
public:
	IdleAction(sf::Sprite* sprite, ActiveObjectState* state) : ActionUsingState<ActiveObjectState>(sprite, state){};
	void apply_action() override { m_state->action_type = ActionType::idle; }
};

#endif