#ifndef ENTITY_MANAGER_HEADER
#define ENTITY_MANAGER_HEADER
#include "entity.h"
#include <vector>

const int capacity = 100000;
class EntityManager {
public:
	EntityManager() { 
		std::fill(m_entity_list.begin(), m_entity_list.end(), true);
	}
	Entity create_entity();
	void destroy(Entity entity);
	std::vector<Entity> get_all_alive_entities();
	bool is_alive(const Entity entity) { return !m_entity_list[entity]; } 

private:
	std::vector<bool> m_entity_list = std::vector<bool>(capacity);
};
#endif
