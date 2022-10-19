#include "../include/system/system.h"

void System::register_world(World* world) { m_parent_world = world; }

void System::register_entity(Entity const& entity) { m_registered_entities.push_back(entity); }

void System::unregister_entity(Entity const& entity) {
	for (auto it = m_registered_entities.begin(); it != m_registered_entities.end(); ++it) {
		Entity e = *it;
		if (e.id == entity.id) {
			m_registered_entities.erase(it);
			return;
		}
	}
}

ComponentMask System::get_signature() { return m_signature; }
