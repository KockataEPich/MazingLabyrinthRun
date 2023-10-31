// ################## THIS FILE IS GENERATED ##################
#ifndef TRANSFORM_COMPONENT_HEADER
#define TRANSFORM_COMPONENT_HEADER

#include <component_base/component.h>
#include <SFML/System/Vector2.hpp>
#include <cmath>

struct TransformComponent : public Component<TransformComponent> {
	TransformComponent() = default;
	explicit TransformComponent(
		sf::Vector2f&& position,
		sf::Vector2f&& scale,
		sf::Vector2f&& size) : 
		m_position{position},
		m_scale{scale},
		m_size{size}{};

	sf::Vector2f m_position;
	sf::Vector2f m_scale;
	sf::Vector2f m_size;
};
#endif