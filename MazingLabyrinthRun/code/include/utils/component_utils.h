#ifndef COMPONENT_UTILS_HEADER
#define COMPONENT_UTILS_HEADER

#include <SFML/Graphics/Rect.hpp>
#include <generated/components/data_components/transform_component.h>

inline sf::Vector2f get_scaled_size(const TransformComponent& component) {
	return {component.size.x * std::abs(component.scale.x), component.size.y * component.scale.y};
};

inline sf::FloatRect get_hitbox_based_on_transform_component(const TransformComponent& transform) {
 	auto scaled_size = get_scaled_size(transform);
	return {transform.position.x - scaled_size.x * 0.275f,
			transform.position.y - scaled_size.y * 0.10f,
	        scaled_size.x * 0.55f,
	        scaled_size.y * 0.50f};
}



#endif