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
	sf::Vector2f center_initiator = initiator_boundary.hitbox.getPosition() + initiator_boundary.hitbox.getSize() / 2;  
	sf::Vector2f d_vel_temp = initiator_velocity.next_frame_location - center_initiator;
	sf::Vector2f d_vel = initiator_velocity.next_frame_location - center_initiator;

	d_vel += collision_info.contact_normal * sf::Vector2f(std::abs(d_vel.x), std::abs(d_vel.y)) * (1 - collision_info.contact_time);
//	if (collision_info.contact_normal.x != 0)
//		d_vel.x *= 0.005f;
//	else if (collision_info.contact_normal.y != 0)
//		d_vel.y *= 0.005f;

	//float x_percentage = std::abs(d_vel_temp.x) / + d_vel.y / x_percentage;
	//d_vel.x *= 0.005f * x_above_y;
	//initiator_velocity.next_frame_location += d_vel;

	auto next_pos_center = center_initiator + d_vel;
	initiator_boundary.hitbox.left = next_pos_center.x - initiator_boundary.hitbox.getSize().x / 2;
	initiator_boundary.hitbox.top = next_pos_center.y - initiator_boundary.hitbox.getSize().y / 2;
	initiator_transform.position = get_transform_position_based_on_boundary(initiator_boundary, get_scaled_size(initiator_transform));
	//nitiator_transform.position = initiator_velocity.next_frame_location;

}