#ifndef ACTION_TYPE_COMPONENT_HEADER
#define ACTION_TYPE_COMPONENT_HEADER

#include "../attribute/action_type.h"

struct ActionTypeComponent : public Component<ActionTypeComponent> {
	explicit ActionTypeComponent(ActionType&& action_type) : m_action_type{std::move(action_type)} {};
	ActionTypeComponent() = default;
	ActionType m_action_type = ActionType::idle;
};

#endif