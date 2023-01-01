#include "../include/entity_base/entity_manager.h"

Entity EntityManager::create_entity() {
	last_entity++;
	return {last_entity};
}

void EntityManager::destroy(Entity entity) {}
