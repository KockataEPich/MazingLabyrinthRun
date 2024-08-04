#include <generated/systems/event_systems/move_system.h>

#include <generated/events/possibly_coliding_with_something_event.h>
#include <generated/events/update_transform_from_boundary_event.h>

#include <utils/component_utils.h>

void MoveSystem::p_handle_event(
	EntityHandle entity,
	TransformComponent& transform,
	SpeedComponent& speed,
    VelocityComponent& velocity,
	BoundaryComponent& boundary,

    MoveEvent& move) { 

	m_game->quad_tree->remove(entity.entity);

	velocity.origin = boundary.hitbox.getPosition() + boundary.hitbox.getSize() * 0.5f; 
	
	velocity.velocity = velocity.calculate_velocity_function(velocity.origin, velocity.final_destination, speed.speed);
	entity.receive_event(PossiblyColidingWithSomethingEvent());
	
	if (!m_game->entities->is_alive(entity.entity)) return;

	velocity.origin += velocity.velocity;

	boundary.hitbox.left = velocity.origin.x - boundary.hitbox.getSize().x * 0.5f;
	boundary.hitbox.top = velocity.origin.y - boundary.hitbox.getSize().y * 0.5f;

	entity.receive_event(UpdateTransformFromBoundaryEvent());
	m_game->quad_tree->insert(entity.entity);
}

