#ifndef ACTIVE_OBJECT_STATE_HEADER_H
#define ACTIVE_OBJECT_STATE_HEADER_H

#include "../../attribute/action_type.h"
#include "../logic/event.h"

struct ActiveObjectState {
	float delta_time;
	ActionType action_type;
};

class IdleAction : public EventUsingState<ActiveObjectState> {
public:
	IdleAction(sf::Sprite* sprite, ActiveObjectState* state) : EventUsingState<ActiveObjectState>(sprite, state){};
	void event() override { m_state->action_type = ActionType::idle; }
};

#endif