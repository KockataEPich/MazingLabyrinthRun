#include "../include/entity/entityManager.h"

Entity EntityManager::createEntity() {
	lastEntity++;
	return {lastEntity};
}

void EntityManager::destroy(Entity entity) {}
