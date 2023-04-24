#include <component_base/component_handle.h>
#include <components/event_components/update_solid_event_component.h>
#include <system/systems/react_systems/collision_detection_system.h>

void CollisionDetection::react(Entity const& entity) {
	m_parent_world->add_event_component(entity, std::make_unique<UpdateSolidEventComponent>());

	ComponentHandle<SolidComponent> solid;
	m_parent_world->unpack(entity, solid);

	for (auto solid_entity : m_parent_world->get_all_entities_who_have_component<SolidComponent>()) {
		if (entity == solid_entity) continue;
		ComponentHandle<SolidComponent> solid_comp;
		m_parent_world->unpack(solid_entity, solid_comp);
		if (solid->m_hitbox.intersects(solid_comp->m_hitbox))
			m_parent_world->exchange_impulses(entity, solid_entity);
	}
}