#ifndef ENTITY_MAP_HEADER
#define ENTITY_MAP_HEADER
#include "entity.h"

#include <array>
#include <map>

const int MAX_NUMBER_OF_COMPONENTS = 1024;
using ComponentInstance = unsigned int;

struct EntityMap {
	Entity get_entity(ComponentInstance instance) { return m_instance_to_entity.at(instance); }

	ComponentInstance get_instance(Entity entity) { return m_entity_to_instance.at(entity); }

	void add(Entity entity, ComponentInstance instance) {
		m_entity_to_instance.insert({entity, instance});
		m_instance_to_entity.at(instance) = entity;
	}

	void update(Entity entity, ComponentInstance instance) {
		m_entity_to_instance.at(entity) = instance;
		m_instance_to_entity.at(instance) = entity;
	}

	void remove(Entity entity) { m_entity_to_instance.erase(entity); }

	std::map<Entity, ComponentInstance> m_entity_to_instance;
	std::array<Entity, MAX_NUMBER_OF_COMPONENTS> m_instance_to_entity;
};
#endif
