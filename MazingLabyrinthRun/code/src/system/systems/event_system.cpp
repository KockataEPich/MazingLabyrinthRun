#include "../include/system/systems/event_system.h"

#include "../include/component_base/component_handle.h"
void EventSystem::update(float dt) {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<StatusListComponent> status_list_component;
		m_parent_world->unpack(entity, status_list_component);
		status_list_component->m_status_list->apply(dt);
	}
}