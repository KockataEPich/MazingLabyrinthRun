#ifndef TARGET_FOR_DIRECTION_COMPONENT_HEADER
#define TARGET_FOR_DIRECTION_COMPONENT_HEADER

#include <component_base/component.h>
#include <SFML/System/Vector2.hpp>
struct TargetForDirection : public Component<TargetForDirection> {
	TargetForDirection() = default;
	TargetForDirection(sf::Vector2f target_position) 
		: m_target_position{target_position} {};
	sf::Vector2f m_target_position;
};

#endif