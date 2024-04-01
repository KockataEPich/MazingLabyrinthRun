#include <generated/systems/react_systems/collision_detection_system.h>
#include <utils/sfml_vector_helpers.h>
#include <utils/component_utils.h>
#include <utils/collision_utils.h>
#include <utils/sfml_rect_helpers.h>

#include <algorithm>

namespace {
bool valid_values(sf::Vector2f& t_near, sf::Vector2f& t_far) {
	return !(std::isnan(t_far.y) || std::isnan(t_far.x) || std::isnan(t_near.y) || std::isnan(t_near.x));
}

void sort_near_and_far(float& near, float& far) { if (near > far) std::swap(near, far);}

sf::Vector2f determine_contact_normal(sf::Vector2f& t_near, 
									  sf::Vector2f& inverse_velocity, 
									  float contact_time) { 
	if (t_near.x == t_near.y) return sf::Vector2f(0, 0); 

	// The offset needed has a buffer. Ideally it would be 1,
	// however with increasing contact time, the offset itself decreases
	// Because of this, an exponential function is applied so that very 
	// little velocity offsets have very high offset_scalars.
	// This ensures that the buffer will exist
	const float offset_scalar = std::max(1.03f, std::powf(1.03f, 15 * contact_time));
	if (t_near.x > t_near.y) return inverse_velocity.x < 0 ? sf::Vector2f(offset_scalar, 0) : sf::Vector2f(-offset_scalar, 0);
	return inverse_velocity.y < 0 ? sf::Vector2f(0, offset_scalar) : sf::Vector2f(0, -offset_scalar);
}

bool dynamic_ray_vs_rect(VelocityComponent& velocity,
                         sf::FloatRect victim_hitbox,
                         CollisionInfo& collision_info) {

	sf::Vector2f inverse_velocity = 1 / velocity.velocity;

	sf::Vector2f t_near = (victim_hitbox.getPosition() - velocity.origin) * inverse_velocity;
	sf::Vector2f t_far = 
		(victim_hitbox.getPosition() + victim_hitbox.getSize() - velocity.origin) * inverse_velocity;

	if (!valid_values(t_near, t_far)) return false;
	do_on_x_and_y(t_near, t_far, {sort_near_and_far});

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	if (std::min(t_far.x, t_far.y) < 0) return false;

	collision_info.contact_time = std::max(t_near.x, t_near.y);

	normalize_float(collision_info.contact_time, 0.009, 0);

	// Float imprecision means that 1.001 should be a hit
	if (collision_info.contact_time >= 1.0 && collision_info.contact_time < 1.02) collision_info.contact_time = 0.9999;

	collision_info.contact_point = velocity.origin + collision_info.contact_time * velocity.velocity;
	collision_info.contact_normal = determine_contact_normal(t_near, inverse_velocity, collision_info.contact_time);

	bool is_hit = collision_info.contact_time >= 0.0 && collision_info.contact_time < 1.0;
	
	// Very high contact time eg 0.99999 creates a very small offset. This means that float imprecision would not be able to increase the offset.
	// And then, this means that two objects will clip into each other
	if (collision_info.contact_time > 0.98) collision_info.contact_time = 0.98;

	return is_hit;
}

std::optional<std::pair<Entity, CollisionInfo>> get_closest_entity(std::set<Entity>& all_possible_collisions,
                                                                   Game* game,
                                                                   VelocityComponent& velocity,
                                                                   BoundaryComponent& boundary) {
	std::optional<std::pair<Entity, CollisionInfo>> closest_entity = std::nullopt;


	for (auto victim_entity : all_possible_collisions) {
		auto [victim_boundary] = game->components->unpack<BoundaryComponent>(victim_entity);
		CollisionInfo collision_info;
		if (dynamic_ray_vs_rect(velocity,
		                        get_expanded_rectangle(victim_boundary->hitbox, boundary.hitbox.getSize()),
		                        collision_info)) {
			if (!closest_entity || collision_info.contact_time < closest_entity->second.contact_time)
				closest_entity = {victim_entity, collision_info};
		}

	}

	return closest_entity;
}


}  // namespace
void CollisionDetectionSystem::react_on_entity(
	EntityHandle entity,
	BoundaryComponent& boundary,
    VelocityComponent& velocity) {

	auto potential_collisions = m_game->quad_tree->get_potential_collisions(boundary.hitbox, velocity.velocity);
	auto closest_entity = get_closest_entity(potential_collisions, m_game, velocity, boundary);
	while (closest_entity.has_value()) {
		m_game->systems->exchange_impulses(entity.entity, closest_entity->first, closest_entity->second);
		potential_collisions.erase(closest_entity->first);
		closest_entity = get_closest_entity(potential_collisions, m_game, velocity, boundary);
	}
}

