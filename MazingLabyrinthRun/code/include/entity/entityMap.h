#ifndef ENTITY_MAP_HEADER
#define ENTITY_MAP_HEADER
#include "entity.h"

#include <array>
#include <map>

const int MAX_NUMBER_OF_COMPONENTS = 1024;
using ComponentInstance = unsigned int;

struct EntityMap {
	Entity getEntity(ComponentInstance instance) { return instanceToEntity.at(instance); }

	ComponentInstance getInstance(Entity entity) { return entityToInstance.at(entity); }

	void add(Entity entity, ComponentInstance instance) {
		entityToInstance.insert({entity, instance});
		instanceToEntity.at(instance) = entity;
	}

	void update(Entity entity, ComponentInstance instance) {
		entityToInstance.at(entity) = instance;
		instanceToEntity.at(instance) = entity;
	}

	void remove(Entity entity) { entityToInstance.erase(entity); }

	std::map<Entity, ComponentInstance> entityToInstance;
	std::array<Entity, MAX_NUMBER_OF_COMPONENTS> instanceToEntity;
};
#endif
