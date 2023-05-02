#ifndef BOUNDARY_COMPONENT_HEADER
#define BOUNDARY_COMPONENT_HEADER

#include <component_base/component.h>
#include <components/data_components/transform_component.h>
#include <SFML/Graphics/Rect.hpp>

struct BoundaryComponent : public Component<BoundaryComponent> {
	BoundaryComponent() = default;
	BoundaryComponent(sf::FloatRect hitbox) : m_hitbox{hitbox} {};
	sf::FloatRect m_hitbox;
};

inline sf::FloatRect get_hitbox_based_on_transform_component(TransformComponent& transform) {
 	auto scaled_size = get_scaled_size(transform);
	return {transform.m_position.x - scaled_size.x * 0.275f,
			transform.m_position.y - scaled_size.y * 0.10f,
	        scaled_size.x * 0.55f,
	        scaled_size.y * 0.50f};
}

#endif