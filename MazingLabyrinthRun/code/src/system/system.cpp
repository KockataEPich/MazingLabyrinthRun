#include "../include/system/system.h"

void System::unregister_entity(Entity const& entity) {
	auto entity_inside = std::find(m_registered_entities.begin(), m_registered_entities.end(), entity);
	if(entity_inside == m_registered_entities.end()) return;

	std::swap(*entity_inside, m_registered_entities.back());
	m_registered_entities.pop_back();
}


