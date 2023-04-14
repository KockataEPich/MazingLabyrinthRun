#ifndef TRANSFORMABLE_COMPONENT_HEADER
#define TRANSFORMABLE_COMPONENT_HEADER

#include "../component_base/component.h"

#include <SFML/System/Vector2.hpp>
struct TransformComponent : public Component<TransformComponent> {
	TransformComponent() = default;
	TransformComponent(sf::Vector2f&& position, 
					   sf::Vector2f&& scale)
	    : m_position{position}
	    , m_scale{scale} {};
	sf::Vector2f m_position;
	sf::Vector2f m_scale;
};

#endif