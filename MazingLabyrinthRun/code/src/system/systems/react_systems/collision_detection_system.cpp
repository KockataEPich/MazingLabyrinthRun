#include <component_base/component_handle.h>
#include <system/systems/react_systems/collision_detection_system.h>

void CollisionDetection::react(Entity const& entity) {
	ComponentHandle<BoundaryComponent> boundary;
	ComponentHandle<TransformComponent> transform;
	m_parent_world->unpack(entity, boundary, transform);

	boundary->m_hitbox = get_hitbox_based_on_transform_component(*transform);

	for (auto victim_entity : m_parent_world->get_all_entities_who_have_component<BoundaryComponent>()) {
		if (entity == victim_entity) continue;
		ComponentHandle<BoundaryComponent> victim_boundary;
		m_parent_world->unpack(victim_entity, victim_boundary);
		if (boundary->m_hitbox.intersects(victim_boundary->m_hitbox))
			m_parent_world->exchange_impulses(entity, victim_entity);
	}
}