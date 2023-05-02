#ifndef TRANSFORMABLE_COMPONENT_HEADER
#define TRANSFORMABLE_COMPONENT_HEADER

#include <component_base/component.h>

#include <SFML/System/Vector2.hpp>
#include <cmath>
struct TransformComponent : public Component<TransformComponent> {
	TransformComponent() = default;
	TransformComponent(sf::Vector2f&& position, 
					   sf::Vector2f&& scale, 
					   sf::Vector2f&& size)
	    : m_position{position}
	    , m_scale{scale}
	    , m_size{size} {};
	sf::Vector2f m_position;
	sf::Vector2f m_scale;
	sf::Vector2f m_size;
};


const inline sf::Vector2f get_scaled_size(const TransformComponent& component) {
	return {component.m_size.x * std::abs(component.m_scale.x),
		    component.m_size.y * component.m_scale.y};
};



#endif