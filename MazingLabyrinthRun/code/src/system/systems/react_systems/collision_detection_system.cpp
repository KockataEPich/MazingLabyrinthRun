#include <generated/systems/react_systems/collision_detection_system.h>
#include <utils/component_utils.h>
#include <utils/collision_utils.h>

namespace {

sf::FloatRect construct_expanded_target(const sf::FloatRect& victim_hitbox, const sf::Vector2f& initiator_size) {
	return {victim_hitbox.getPosition().x - initiator_size.x * 0.5f,
	        victim_hitbox.getPosition().y - initiator_size.y * 0.5f,
	        victim_hitbox.getSize().x + initiator_size.x,
	        victim_hitbox.getSize().y + initiator_size.y};
}

bool valid_values(sf::Vector2f& t_near, sf::Vector2f& t_far) {
	return !(std::isnan(t_far.y) || std::isnan(t_far.x) || std::isnan(t_near.y) || std::isnan(t_near.x));
}

void sort_near_and_far(sf::Vector2f& t_near, sf::Vector2f& t_far) {
	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);
}

sf::Vector2f determine_contact_normal(sf::Vector2f& t_near, sf::Vector2f& inverse_velocity) {
	const float offset_corner = 0.01;
	if (t_near.x == t_near.y) { 
		float x = inverse_velocity.x < 0 ? offset_corner : offset_corner * -1;
		float y = inverse_velocity.y < 0 ? offset_corner : offset_corner * -1;
		return sf::Vector2f(x, y); 
	}
	if (t_near.x > t_near.y) return (inverse_velocity.x < 0) ? sf::Vector2f(1.02, 0) : sf::Vector2f(-1.02, 0);
	return (inverse_velocity.y < 0) ? sf::Vector2f(0, 1.02) : sf::Vector2f(0, -1.02);
}

bool dynamic_ray_vs_rect(VelocityComponent& velocity,
                         sf::FloatRect victim_hitbox,
                         CollisionInfo& collision_info) {

	sf::Vector2f inverse_velocity = 1 / velocity.velocity;

	sf::Vector2f t_near = (victim_hitbox.getPosition() - velocity.origin) * inverse_velocity;
	sf::Vector2f t_far = (victim_hitbox.getPosition() + victim_hitbox.getSize() - velocity.origin) * inverse_velocity;

	if (!valid_values(t_near, t_far)) return false;
	sort_near_and_far(t_near, t_far);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	if (std::min(t_far.x, t_far.y) < 0) return false;

	collision_info.contact_time = std::max(t_near.x, t_near.y);
	normalize_float(collision_info.contact_time);

	collision_info.contact_point = velocity.origin + collision_info.contact_time * velocity.velocity;
	collision_info.contact_normal = determine_contact_normal(t_near, inverse_velocity);

	return collision_info.contact_time >= 0.0 && collision_info.contact_time < 1.0;
}
}  // namespace
void CollisionDetectionSystem::react_on_entity(
	EntityHandle entity,
	BoundaryComponent& boundary,
	TransformComponent& transform,
    VelocityComponent& velocity) {

	hit_count++; 
	auto potential_collisions = m_game->quad_tree->get_potential_collisions(boundary.hitbox, velocity.velocity);
	auto bottom_left_point = boundary.hitbox.getPosition() + boundary.hitbox.getSize();
	Entity intersected_entity; 
    for (auto victim_entity : potential_collisions) {
		auto [victim_boundary] = m_game->components->unpack<BoundaryComponent>(victim_entity);
		if (boundary.hitbox.intersects(victim_boundary->hitbox)) { 
			intersected_entity = victim_entity;	
		}
	}
	for (auto victim_entity : potential_collisions) {
		auto [victim_boundary] = m_game->components->unpack<BoundaryComponent>(victim_entity);
		CollisionInfo collision_info;
		if (dynamic_ray_vs_rect(velocity, construct_expanded_target(victim_boundary->hitbox, boundary.hitbox.getSize()), collision_info)) {
			m_game->systems->exchange_impulses(entity.entity, victim_entity, collision_info);
		}
	}

}

