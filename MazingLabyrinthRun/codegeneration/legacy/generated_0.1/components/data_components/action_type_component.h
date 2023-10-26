// ################## THIS FILE IS GENERATED ##################
#ifndef ACTION_TYPE_COMPONENT_HEADER
#define ACTION_TYPE_COMPONENT_HEADER

#include <component_base/component.h>
#include <attribute/action_type.h>

struct ActionTypeComponent : public Component<ActionTypeComponent> {
	ActionTypeComponent() = default;
	explicit ActionTypeComponent(
		ActionType&& action_type) : 
		m_action_type{action_type}{};

	ActionType m_action_type = ActionType::idle;
};
#endif