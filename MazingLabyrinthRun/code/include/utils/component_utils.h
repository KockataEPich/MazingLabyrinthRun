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


inline sf::FloatRect get_hitbox_based_on_transform_component(const TransformComponent& transform) {
 	auto scaled_size = get_scaled_size(transform);
	return {transform.position.x - scaled_size.x * 0.275f,
			transform.position.y - scaled_size.y * 0.10f,
	        scaled_size.x * 0.55f,
	        scaled_size.y * 0.50f};
}

inline sf::Vector2f update_boundary_and_get_transform_based_on_velocity(const VelocityComponent velocity,
                                                                        BoundaryComponent& boundary,
																        sf::Vector2f scaled_size) {
	boundary.hitbox.left = velocity.origin.x - boundary.hitbox.getSize().x * 0.5f;
	boundary.hitbox.top = velocity.origin.y - boundary.hitbox.getSize().y * 0.5f;

	return {boundary.hitbox.left + scaled_size.x * 0.275f, boundary.hitbox.top + scaled_size.y * 0.10f};
}

#endif