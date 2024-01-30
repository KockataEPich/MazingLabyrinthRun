#include <generated/systems/react_systems/collision_detection_system.h>
#include <utils/component_utils.h>


void CollisionDetectionSystem::react_on_entity(
	Entity entity,
	BoundaryComponent& boundary,
	TransformComponent& transform,
    TargetForDirectionComponent& target_for_direction) {

	boundary.hitbox = get_hitbox_based_on_transform_component(transform);

	// TODO
	//auto temp = transform.position;
	//transform.position = target_for_direction.target_position;

	//sf::Vector2f 

	for (auto victim_entity : m_game->entities->get_all_entities_who_have_component<BoundaryComponent>()) {
		if (entity == victim_entity) continue;
		auto [victim_boundary] = m_game->components->unpack<BoundaryComponent>(victim_entity);
		if (boundary.hitbox.intersects(victim_boundary->hitbox))
			m_game->systems->exchange_impulses(entity, victim_entity);
	}
}

