#include <generated/systems/react_systems/collision_detection_system.h>
#include <utils/component_utils.h>

void CollisionDetectionSystem::react_on_entity(
	Entity entity,
	BoundaryComponent& boundary,
	TransformComponent& transform){

	boundary.hitbox = get_hitbox_based_on_transform_component(transform);

	for (auto victim_entity : m_parent_world->get_all_entities_who_have_component<BoundaryComponent>()) {
		if (entity == victim_entity) continue;
		ComponentHandle<BoundaryComponent> victim_boundary;
		m_parent_world->unpack(victim_entity, victim_boundary);
		if (boundary.hitbox.intersects(victim_boundary->hitbox))
			m_parent_world->exchange_impulses(entity, victim_entity);
	}
}

