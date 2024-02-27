#include <generated/systems/react_systems/move_system.h>

#include <numbers>  // for std::numbers::pi
#include <generated/components/basic_components/collision_check_component.h>

// EXTRA INCLUDES TODO BE DELETED
#include <generated/components/data_components/boundary_component.h>
#include <utils/component_utils.h>

void MoveSystem::react_on_entity(
	EntityHandle entity,
	TransformComponent& transform,
	SpeedComponent& speed,
    VelocityComponent& velocity) { 

	m_game->quad_tree->remove(entity.entity);

	auto boundary = entity.get_component<BoundaryComponent>();

	// Clearly wrong as moving thing could not have boundary. To be cleaned up after implementation is good
	velocity.origin = boundary->hitbox.getPosition() + boundary->hitbox.getSize() * 0.5f;  

	sf::Vector2f triangle_sides = {std::abs(velocity.origin.x - velocity.final_destination.x),
	                               std::abs(velocity.origin.y - velocity.final_destination.y)};

	auto angle = std::atan2(triangle_sides.y, triangle_sides.x) * 180 / std::numbers::pi;

	auto x_offset = speed.speed * std::cos(std::numbers::pi * 2 * angle / 360);
	auto y_offset = speed.speed * std::sin(std::numbers::pi * 2 * angle / 360);

	velocity.velocity.x = (velocity.origin.x < velocity.final_destination.x) ? (float)x_offset : (float)x_offset * -1;
	velocity.velocity.y = (velocity.origin.y < velocity.final_destination.y) ? (float)y_offset : (float)y_offset * -1;

	entity.add_event_components<CollisionCheckComponent>();
	m_game->quad_tree->insert(entity.entity);
}

