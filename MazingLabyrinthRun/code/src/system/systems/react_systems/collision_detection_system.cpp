#include <generated/systems/react_systems/collision_detection_system.h>
#include <utils/sfml_vector_helpers.h>
#include <utils/component_utils.h>
#include <utils/collision_utils.h>
#include <algorithm>

namespace {

sf::FloatRect construct_expanded_target(const sf::FloatRect& victim_hitbox, 
										const sf::Vector2f& initiator_size) {
	return {victim_hitbox.getPosition().x - initiator_size.x * 0.5f,
	        victim_hitbox.getPosition().y - initiator_size.y * 0.5f,
	        victim_hitbox.getSize().x + initiator_size.x,
	        victim_hitbox.getSize().y + initiator_size.y};
}

bool valid_values(sf::Vector2f& t_near, sf::Vector2f& t_far) {
	return !(std::isnan(t_far.y) || std::isnan(t_far.x) || std::isnan(t_near.y) || std::isnan(t_near.x));
}

void sort_near_and_far(float& near, float& far) { if (near > far) std::swap(near, far);}

sf::Vector2f determine_contact_normal(sf::Vector2f& t_near, 
									  sf::Vector2f& inverse_velocity, 
									  float contact_time) {
	// The offset needed has a buffer. Ideally it would be 1,
	// however with increasing contact time, the offset itself decreases
	// Because of this, an exponential function is applied so that very 
	// little velocity offsets have very high offset_scalars.
	// This ensures that the buffer will exist
	const float offset_scalar = std::max(1.03f, std::powf(1.03f, 15 * contact_time));
	if (t_near.x == t_near.y) return sf::Vector2f(0, 0); 
	if (t_near.x > t_near.y) return (inverse_velocity.x < 0) ? 
									sf::Vector2f(offset_scalar, 0) : sf::Vector2f(-offset_scalar, 0);
	return (inverse_velocity.y < 0) ? sf::Vector2f(0, offset_scalar) : sf::Vector2f(0, -offset_scalar);
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

Entity get_closest_entity(std::set<Entity>& all_possible_collisions, Game* game, VelocityComponent& velocity, BoundaryComponent& boundary) {
	std::vector<std::pair<Entity, float>> sorted_entities;
	for (auto victim_entity : all_possible_collisions) {
		auto [victim_boundary] = game->components->unpack<BoundaryComponent>(victim_entity);
		CollisionInfo collision_info;
		if (dynamic_ray_vs_rect(velocity,
		                        construct_expanded_target(victim_boundary->hitbox, boundary.hitbox.getSize()),
		                        collision_info))
			sorted_entities.push_back({victim_entity, collision_info.contact_time});
	}

	if (sorted_entities.size() == 0) return -1;
	auto min_element = std::min_element(sorted_entities.begin(),
	                                    sorted_entities.end(),
	                                    [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; }); 
	return min_element->first;
}


}  // namespace
void CollisionDetectionSystem::react_on_entity(
	EntityHandle entity,
	BoundaryComponent& boundary,
    VelocityComponent& velocity) {

	auto potential_collisions = m_game->quad_tree->get_potential_collisions(boundary.hitbox, velocity.velocity);
	Entity closest_entity = get_closest_entity(potential_collisions, m_game, velocity, boundary);
	while (closest_entity != -1) {
		auto [victim_boundary] = m_game->components->unpack<BoundaryComponent>(closest_entity);
		CollisionInfo collision_info;
		if (dynamic_ray_vs_rect(velocity,
			                    construct_expanded_target(victim_boundary->hitbox, boundary.hitbox.getSize()),
			                    collision_info)) {
			m_game->systems->exchange_impulses(entity.entity, closest_entity, collision_info);
			potential_collisions.erase(closest_entity);
			closest_entity = get_closest_entity(potential_collisions, m_game, velocity, boundary);
		}
	}

	  // To delete
	 auto total_origin = velocity.origin + velocity.velocity;
     sf::FloatRect after_move_box = boundary.hitbox;
	 after_move_box.left = total_origin.x - after_move_box.getSize().x * 0.5f;
	 after_move_box.top = total_origin.y - after_move_box.getSize().y * 0.5f;
	 for (const auto& possible_collision :
	    m_game->entities->get_all_entities_who_have_component<BoundaryComponent>()) {
		if (possible_collision == entity.entity) continue;
			auto [victim_pop] = m_game->components->unpack<BoundaryComponent>(possible_collision);
		if (after_move_box.intersects(victim_pop->hitbox)) {
			CollisionInfo collision_info_2;
			//dynamic_ray_vs_rect(copy_of_velocity,
			//                    construct_expanded_target(victim_pop->hitbox, boundary.hitbox.getSize()),
			//                    collision_info_2);
			int five = 5;
			
		}
		
	}
}

