#include <generated/systems/impulse_systems/basic_collision_system.h>
#include <utils/component_utils.h>
#include <utils/sfml_vector_helpers.h>

void BasicCollisionSystem::clash_entities(
        EntityHandle initiator,
		VelocityComponent& initiator_velocity,

        EntityHandle victim,

        const CollisionInfo& collision_info
    ){


	sf::Vector2f offset = collision_info.contact_normal * 
						  abs(initiator_velocity.velocity) * 
						  (1 - collision_info.contact_time);

	do_per_x_and_y(offset, initiator_velocity.velocity, {[](float& in, float reference) {
		if (std::abs(reference) - std::abs(in) < 0) in = reference * -1;
	}});
	initiator_velocity.velocity += offset;
	
	do_for_x_and_y(initiator_velocity.velocity, std::function(normalize_float), 0.009f, 0.0f);
}