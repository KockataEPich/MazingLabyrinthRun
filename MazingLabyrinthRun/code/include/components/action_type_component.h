#ifndef ACTION_TYPE_COMPONENT_HEADER
#define ACTION_TYPE_COMPONENT_HEADER

#include "../attribute/action_type.h"
#include "../component_base/component.h"

struct ActionTypeComponent : public Component<ActionTypeComponent> {
	explicit ActionTypeComponent(ActionType&& action_type) : m_action_type{action_type} {};
	ActionTypeComponent() = default;
	ActionType m_action_type = ActionType::idle;
};

#endif