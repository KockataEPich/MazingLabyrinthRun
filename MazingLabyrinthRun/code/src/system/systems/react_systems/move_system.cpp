#include <generated/systems/react_systems/move_system.h>

#include <generated/components/basic_components/collision_check_component.h>
#include <generated/components/basic_components/update_transform_from_boundary_component.h>

#include <numbers>  // for std::numbers::pi
#include <utils/component_utils.h>

namespace {
void determine_velocity(VelocityComponent& velocity, const float speed) {
	sf::Vector2f triangle_sides = {std::abs(velocity.origin.x - velocity.final_destination.x),
	                               std::abs(velocity.origin.y - velocity.final_destination.y)};

	float angle = std::atan2(triangle_sides.y, triangle_sides.x) * 180 / std::numbers::pi;

	float x_offset = speed * std::cos(std::numbers::pi * 2 * angle / 360);
	float y_offset = speed * std::sin(std::numbers::pi * 2 * angle / 360);

	velocity.velocity.x = (velocity.origin.x < velocity.final_destination.x) ? x_offset : x_offset * -1;
	velocity.velocity.y = (velocity.origin.y < velocity.final_destination.y) ? y_offset : y_offset * -1;
}
}
void MoveSystem::react_on_entity(
	EntityHandle entity,
	TransformComponent& transform,
	SpeedComponent& speed,
    VelocityComponent& velocity,
	BoundaryComponent& boundary) { 

//	entity.add_event_components<UpdateTransformFromBoundaryComponent>();
//	entity.add_event_components<UpdateBoundaryFromTransformComponent>();

	m_game->quad_tree->remove(entity.entity);

	velocity.origin = boundary.hitbox.getPosition() + boundary.hitbox.getSize() * 0.5f; 
	
	determine_velocity(velocity, speed.speed);
	entity.add_event_components<CollisionCheckComponent>();
	
	if (!m_game->entities->is_alive(entity.entity)) return;

	velocity.origin += velocity.velocity;

	boundary.hitbox.left = velocity.origin.x - boundary.hitbox.getSize().x * 0.5f;
	boundary.hitbox.top = velocity.origin.y - boundary.hitbox.getSize().y * 0.5f;

	entity.add_event_components<UpdateTransformFromBoundaryComponent>();
	m_game->quad_tree->insert(entity.entity);
}

