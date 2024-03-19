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
	sf::Vector2f offset = collision_info.contact_normal * abs(initiator_velocity.velocity) * (1 - collision_info.contact_time);
	
	if (std::abs(initiator_velocity.velocity.x) - std::abs(offset.x) < 0)
		offset.x = initiator_velocity.velocity.x * -1;
	if (std::abs(initiator_velocity.velocity.y) - std::abs(offset.y) < 0)
		offset.y = initiator_velocity.velocity.y * -1;

	initiator_velocity.velocity += offset;

	normalize_float(initiator_velocity.velocity.x);
	normalize_float(initiator_velocity.velocity.y);

	auto total_origin = initiator_velocity.origin + initiator_velocity.velocity;
	sf::FloatRect after_move_box = initiator_boundary.hitbox;
	after_move_box.left = total_origin.x - after_move_box.getSize().x * 0.5f;
	after_move_box.top = total_origin.y - after_move_box.getSize().y * 0.5f;

	if (after_move_box.intersects(victim_boundary.hitbox)) {
		int five = 5;
	}
}