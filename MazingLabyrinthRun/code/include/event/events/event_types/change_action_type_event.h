#ifndef CHANGE_ACTION_TYPE_EVENT_HEADER
#define CHANGE_ACTION_TYPE_EVENT_HEADER

#include "../event.h"

#include <attribute/action_type.h>
#include <components/action_type_component.h>

class ChangeActionTypeEvent : public Event {
public:
	ChangeActionTypeEvent(ActionTypeComponent& action_type_component, ActionType&& action_type)
	    : m_action_type_component{action_type_component}
	    , m_action_type{action_type} {}

private:
	ActionTypeComponent& m_action_type_component;
	ActionType m_action_type;

	void apply(float dt) override { m_action_type_component.m_action_type = m_action_type; }
};
#endif