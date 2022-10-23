#ifndef TRANSFORMABLE_COMPONENT_HEADER
#define TRANSFORMABLE_COMPONENT_HEADER

#include "../component_base/component.h"

#include <SFML/System/Vector2.hpp>
struct TransformComponent : public Component<TransformComponent> {
	TransformComponent(sf::Vector2<float>&& position, sf::Vector2<float>&& scale)
	    : m_position{position}
	    , m_scale{scale} {};
	sf::Vector2<float> m_position;
	sf::Vector2<float> m_scale;
};

#endif