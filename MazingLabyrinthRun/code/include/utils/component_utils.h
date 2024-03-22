#ifndef COMPONENT_UTILS_HEADER
#define COMPONENT_UTILS_HEADER

#include <SFML/Graphics/Rect.hpp>
#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/boundary_component.h>
#include <generated/components/data_components/velocity_component.h>

inline sf::Vector2f operator/(sf::Vector2f lhs, sf::Vector2f rhs) { 
	return {lhs.x / rhs.x, lhs.y / rhs.y}; 
}

inline sf::Vector2f operator*(sf::Vector2f lhs, sf::Vector2f rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y}; }

inline sf::Vector2f operator/(float lhs, sf::Vector2f rhs) { return {lhs / rhs.x, lhs / rhs.y}; }
inline sf::Vector2f operator/(sf::Vector2f lhs, int rhs) { return {lhs.x / rhs, lhs.y / rhs}; }

inline sf::Vector2f get_scaled_size(const TransformComponent& component) {
	return {component.size.x * std::abs(component.scale.x), component.size.y * component.scale.y};
};

inline sf::Vector2f abs(sf::Vector2f vec) { return {std::abs(vec.x), std::abs(vec.y)}; }

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

inline void normalize_float(float& input) { if (input < 0.009f && input > -0.009f) input = 0; }

#endif