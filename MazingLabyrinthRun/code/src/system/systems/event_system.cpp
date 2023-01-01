#include "../include/system/systems/event_system.h"

void EventSystem::update(float dt) {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<CompositeEventComponent> events;
		m_parent_world->unpack(entity, events);
		events->m_events->happen(dt);
	}
}