// ################## THIS FILE IS GENERATED ##################
#ifndef TARGET_FOR_DIRECTION_COMPONENT_HEADER
#define TARGET_FOR_DIRECTION_COMPONENT_HEADER

#include <component_base/component.h>
#include <SFML/System/Vector2.hpp>

struct TargetForDirectionComponent : public Component<TargetForDirectionComponent> {
	TargetForDirectionComponent() = default;
	explicit TargetForDirectionComponent(
		sf::Vector2f&& target_position) : 
		m_target_position{target_position}{};

	sf::Vector2f m_target_position;
};
#endif