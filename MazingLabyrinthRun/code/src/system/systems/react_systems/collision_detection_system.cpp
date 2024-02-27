#include <generated/systems/react_systems/collision_detection_system.h>
#include <utils/component_utils.h>
#include <utils/collision_utils.h>

bool dynamic_ray_vs_rect(VelocityComponent& velocity,
                         sf::FloatRect& victim_boundary,
                         BoundaryComponent& initiator_boundary,
                         CollisionInfo& collision_info) {

	sf::Vector2f center_initiator = initiator_boundary.hitbox.getPosition() + initiator_boundary.hitbox.getSize() / 2;  

	sf::Vector2f dvec = velocity.velocity;
	sf::Vector2f inverse_target_position = 1.0f / dvec;

	sf::Vector2f t_near = (victim_boundary.getPosition() - center_initiator) * inverse_target_position;
	sf::Vector2f t_far = (victim_boundary.getPosition() + victim_boundary.getSize() - center_initiator) * inverse_target_position;

	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0) return false;

	collision_info.contact_time = std::max(t_near.x, t_near.y);

	// Contact point of collision from parametric line equation
	collision_info.contact_point = center_initiator + collision_info.contact_time * dvec;
	 if (t_near.x > t_near.y)
		if (inverse_target_position.x < 0) collision_info.contact_normal = {1, 0};
		else collision_info.contact_normal = {-1, 0};
	else if (t_near.x < t_near.y)
		if (inverse_target_position.y < 0) collision_info.contact_normal = {0, 1};
		else collision_info.contact_normal = {0, -1};
   
	return true;
}

bool dynamic_rect_vs_rect(VelocityComponent& velocity,
						 BoundaryComponent& initiator_boundary,
                         BoundaryComponent& victim_boundary,
                         CollisionInfo& collision_info) {

	// Expand target rectangle by source dimensions
	sf::FloatRect expanded_target;
	expanded_target.left = (victim_boundary.hitbox.getPosition() - initiator_boundary.hitbox.getSize() / 2).x;
	expanded_target.top = (victim_boundary.hitbox.getPosition() - initiator_boundary.hitbox.getSize() / 2).y;

	expanded_target.width = victim_boundary.hitbox.getSize().x + initiator_boundary.hitbox.getSize().x;
	expanded_target.height = victim_boundary.hitbox.getSize().y + initiator_boundary.hitbox.getSize().y;

	if (dynamic_ray_vs_rect(velocity, expanded_target, initiator_boundary, collision_info)) {
		return collision_info.contact_time >= 0.0f && collision_info.contact_time < 1.0f;
	} 
	
	return false;
}

void CollisionDetectionSystem::react_on_entity(
	EntityHandle entity,
	BoundaryComponent& boundary,
	TransformComponent& transform,
    VelocityComponent& velocity) {

	bool collision_happened = false;
	auto neighbours = m_game->quad_tree->get_neighbours(entity.entity);
	for (auto victim_entity : neighbours) {
		if (entity.entity == victim_entity) continue;

		// Check if entity has boundary
		ComponentMask boundary_component_mask;
		boundary_component_mask.add_components<BoundaryComponent>();
		if (!m_game->entities->get_mask(victim_entity).matches(boundary_component_mask)) return;

		auto [victim_boundary] = m_game->components->unpack<BoundaryComponent>(victim_entity);
		CollisionInfo collision_info;
		if (dynamic_rect_vs_rect(velocity, boundary, *victim_boundary, collision_info)) {
		 m_game->systems->exchange_impulses(entity.entity, victim_entity, collision_info);
		 collision_happened = true;
		}
	}

	if (!collision_happened) {
		sf::Vector2f center_initiator = boundary.hitbox.getPosition() + boundary.hitbox.getSize() / 2;
		boundary.hitbox.left = center_initiator.x + velocity.velocity.x - boundary.hitbox.getSize().x / 2;
		boundary.hitbox.top = center_initiator.y + velocity.velocity.y - boundary.hitbox.getSize().y / 2;
		transform.position = get_transform_position_based_on_boundary(boundary, get_scaled_size(transform));
	}


}

