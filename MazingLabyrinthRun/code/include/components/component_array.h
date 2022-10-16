#ifndef BASE_COMPONENT_ARRAY_HEADER_H
#define BASE_COMPONENT_ARRAY_HEADER_H

#include "../entity/entity.h"

#include <array>
#include <assert.h>
#include <bitset>
#include <numeric>
#include <unordered_map>

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void entity_destroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
	void insert_data(Entity entity, T component) {
		assert(m_entity_to_index_map.find(entity) == m_entity_to_index_map.end() &&
		       "Component added to same entity more than once.");

		// Put new entry at end and update the maps
		size_t newIndex = m_size;
		m_entity_to_index_map[entity] = newIndex;
		m_index_to_entity_map[newIndex] = entity;
		m_component_array[newIndex] = component;
		++m_size;
	}

	void remove_data(Entity entity) {
		assert(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = m_entity_to_index_map[entity];
		size_t indexOfLastElement = m_size - 1;
		m_component_array[indexOfRemovedEntity] = m_component_array[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = m_index_to_entity_map[indexOfLastElement];
		m_entity_to_index_map[entityOfLastElement] = indexOfRemovedEntity;
		m_index_to_entity_map[indexOfRemovedEntity] = entityOfLastElement;

		m_entity_to_index_map.erase(entity);
		m_index_to_entity_map.erase(indexOfLastElement);

		--m_size;
	}

	T& get_data(Entity entity) {
		assert(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end() &&
		       "Retrieving non-existent component.");

		// Return a reference to the entity's component
		return m_component_array[m_entity_to_index_map[entity]];
	}

	void entity_destroyed(Entity entity) override {
		if (m_entity_to_index_map.find(entity) != m_entity_to_index_map.end()) {
			// Remove the entity's component if it existed
			remove_data(entity);
		}
	}

private:
	// The packed array of components (of generic type T),
	// set to a specified maximum amount, matching the maximum number
	// of entities allowed to exist simultaneously, so that each entity
	// has a unique spot.
	std::array<T, MAX_ENTITIES> m_component_array;

	// Map from an entity ID to an array index.
	std::unordered_map<Entity, size_t> m_entity_to_index_map;

	// Map from an array index to an entity ID.
	std::unordered_map<size_t, Entity> m_index_to_entity_map;

	// Total size of valid entries in the array.
	size_t m_size;
};

#endif