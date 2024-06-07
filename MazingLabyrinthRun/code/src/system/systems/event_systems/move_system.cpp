#include <generated/systems/event_systems/move_system.h>

#include <generated/events/possibly_coliding_event.h>
#include <generated/events/update_transform_from_boundary_event.h>

#include <numbers>  // for std::numbers::pi
#include <utils/component_utils.h>

namespace {
void determine_velocity(VelocityComponent& velocity, const float speed) {
	sf::Vector2f triangle_sides = {std::abs(velocity.origin.x - velocity.final_destination.x),
	                               std::abs(velocity.origin.y - velocity.final_destination.y)};

	float angle = std::atan2(triangle_sides.y, triangle_sides.x) * 180 / std::numbers::pi;
	float angle_end_point = std::numbers::pi * 2 * angle / 360;

	float x_offset = speed * std::cos(angle_end_point);
	float y_offset = speed * std::sin(angle_end_point);

	velocity.velocity.x = (velocity.origin.x < velocity.final_destination.x) ? x_offset : x_offset * -1;
	velocity.velocity.y = (velocity.origin.y < velocity.final_destination.y) ? y_offset : y_offset * -1;
}
}  // namespace
void MoveSystem::p_handle_event(
	EntityHandle entity,
	TransformComponent& transform,
	SpeedComponent& speed,
    VelocityComponent& velocity,
	BoundaryComponent& boundary,
    MoveEvent& move) { 

	m_game->quad_tree->remove(entity.entity);

	velocity.origin = boundary.hitbox.getPosition() + boundary.hitbox.getSize() * 0.5f; 
	
	determine_velocity(velocity, speed.speed);
	entity.receive_event(PossiblyColidingEvent());
	
	if (!m_game->entities->is_alive(entity.entity)) return;

	velocity.origin += velocity.velocity;

	boundary.hitbox.left = velocity.origin.x - boundary.hitbox.getSize().x * 0.5f;
	boundary.hitbox.top = velocity.origin.y - boundary.hitbox.getSize().y * 0.5f;

	entity.receive_event(UpdateTransformFromBoundaryEvent());
	m_game->quad_tree->insert(entity.entity);
}

