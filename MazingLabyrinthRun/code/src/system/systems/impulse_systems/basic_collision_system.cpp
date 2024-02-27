#include <generated/systems/impulse_systems/basic_collision_system.h>
#include <utils/component_utils.h>

void BasicCollisionSystem::clash_entities(
        EntityHandle initiator,
        TransformComponent& initiator_transform,
		SpeedComponent& initiator_speed,
		FacingSideComponent& initiator_facing_side,
		VelocityComponent& initiator_velocity,
        BoundaryComponent& initiator_boundary,

        EntityHandle victim,
		BoundaryComponent& victim_boundary,

        const CollisionInfo& collision_info
    ){


	initiator_velocity.velocity += collision_info.contact_normal 
											* sf::Vector2f(std::abs(initiator_velocity.velocity.x),
	                                                       std::abs(initiator_velocity.velocity.y)) 
											* (1 - collision_info.contact_time);

	sf::Vector2f center_initiator =
	    initiator_boundary.hitbox.getPosition() + initiator_boundary.hitbox.getSize() * 0.5f;  

	auto next_pos_center = center_initiator + initiator_velocity.velocity;
	initiator_boundary.hitbox.left = next_pos_center.x - initiator_boundary.hitbox.getSize().x * 0.5;
	initiator_boundary.hitbox.top = next_pos_center.y - initiator_boundary.hitbox.getSize().y * 0.5;
	initiator_transform.position = get_transform_position_based_on_boundary(initiator_boundary, get_scaled_size(initiator_transform));
}