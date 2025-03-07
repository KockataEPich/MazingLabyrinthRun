#ifndef COMPONENT_UTILS_HEADER
#define COMPONENT_UTILS_HEADER

#include <SFML/Graphics/Rect.hpp>
#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/boundary_component.h>
#include <generated/components/data_components/velocity_component.h>

inline sf::Vector2f get_scaled_size(const TransformComponent& component) {
	return component.size * component.scale;
};

inline sf::FloatRect get_hitbox_based_on_transform_component(const TransformComponent& transform) {
 	auto scaled_size = get_scaled_size(transform);
	return {transform.position.x - scaled_size.x * 0.275f,
			transform.position.y - scaled_size.y * 0.10f,
	        scaled_size.x * 0.55f,
	        scaled_size.y * 0.50f};
}

inline sf::Vector2f get_transform_based_on_boundary_component(BoundaryComponent& boundary,sf::Vector2f scaled_size) {
	return {boundary.hitbox.left + scaled_size.x * 0.275f, boundary.hitbox.top + scaled_size.y * 0.10f};
}

inline void normalize_float(float& input, float range, float normalized_value) { 
	if (input < range && input > -range) input = normalized_value;
}

#endif