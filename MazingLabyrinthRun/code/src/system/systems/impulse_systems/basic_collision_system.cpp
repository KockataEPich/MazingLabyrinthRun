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
}