#include <generated/systems/react_systems/move_system.h>

#include <numbers>  // for std::numbers::pi
#include <generated/components/basic_components/collision_check_component.h>

// EXTRA INCLUDES TODO BE DELETED
#include <generated/components/data_components/boundary_component.h>
#include <utils/component_utils.h>

namespace {

sf::Vector2f get_next_unobstructed_position(const sf::Vector2f& origin,
                                            const SpeedComponent& speed,
                                            const sf::Vector2f& target_point) {

	sf::Vector2f triangle_sides = {std::abs(origin.x - target_point.x),
	                               std::abs(origin.y - target_point.y)};

	auto atan_val = std::atan2(triangle_sides.y, triangle_sides.x);
	auto angle = atan_val * 180 / std::numbers::pi;

	auto x_offset = speed.speed * std::cos(std::numbers::pi * 2 * angle / 360);
	auto y_offset = speed.speed * std::sin(std::numbers::pi * 2 * angle / 360);

	auto new_x = (origin.x < target_point.x) ? origin.x + (float)x_offset
	                                                              : origin.x - (float)x_offset;

	auto new_y = (origin.y < target_point.y) ? origin.y + (float)y_offset
	                                                              : origin.y - (float)y_offset;

	return {new_x, new_y};
}

}  // namespace


void MoveSystem::react_on_entity(
	EntityHandle entity,
	TransformComponent& transform,
	SpeedComponent& speed,
    VelocityComponent& velocity) { 

	m_game->quad_tree->remove(entity.entity);
	
	// Clearly wrong as moving thing could not have boundary. To be cleaned up after implementation is good
	auto boundary = entity.get_component<BoundaryComponent>();

	sf::Vector2f center_boundary = boundary->hitbox.getPosition() + boundary->hitbox.getSize() * 0.5f;  
	velocity.next_frame_location = get_next_unobstructed_position(center_boundary, speed, velocity.target_point);

	entity.add_event_components<CollisionCheckComponent>();

	m_game->quad_tree->insert(entity.entity);
}

