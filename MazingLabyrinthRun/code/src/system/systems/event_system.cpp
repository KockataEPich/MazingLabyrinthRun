#include "../include/system/systems/event_system.h"

void EventSystem::update() {
	for (auto& entity : m_registered_entities) {
		//ComponentHandle<CompositeEventComponent> events;
		//m_parent_world->unpack(entity, events);
		//events->m_events->happen(dt);
	}
}