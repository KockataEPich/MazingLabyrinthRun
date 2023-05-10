#include "../include/entity_base/entity_manager.h"
#include <component_base/component.h>
Entity EntityManager::create_entity() { 
	int entity = std::find(m_entity_list.begin(), m_entity_list.end(), true) - m_entity_list.begin();
	m_entity_list[entity] = false;
	return entity;
}
void EntityManager::destroy(Entity entity) {m_entity_list[entity] = true;}
