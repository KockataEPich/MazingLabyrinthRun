#include "../include/entity_base/entity_manager.h"
#include <component_base/component.h>
Entity EntityManager::create_entity() { 
	int entity = std::find(m_entity_list.begin(), m_entity_list.end(), true) - m_entity_list.begin();
	m_entity_list[entity] = false;
	return entity;
}

std::vector<Entity> EntityManager::get_all_alive_entities() {
	std::vector<Entity> alive_entities;

	for (int entity = 0; entity < m_entity_list.size(); entity++)
		if (!m_entity_list[entity]) 
			alive_entities.push_back(entity);

	return alive_entities;
}

void EntityManager::destroy(Entity entity) {m_entity_list[entity] = true;}
