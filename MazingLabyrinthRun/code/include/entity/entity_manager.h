#ifndef BASE_ENTITY_MANAGER_HEADER
#define BASE_ENTITY_MANAGER_HEADER
#include "entity.h"
#include "component.h"

#include <assert.h>
#include <queue>
#include <array>
#include <bitset>
#include <numeric>

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager {
public:
	EntityManager() {
		// Initialize the queue with all possible entity IDs
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) { m_available_entities.push(entity); }
	}

	Entity create_entity() {
		assert(m_living_entities_count < MAX_ENTITIES && "Too many entities in existence.");

		// Take an ID from the front of the queue
		Entity id = m_available_entities.front();
		m_available_entities.pop();
		++m_living_entities_count;

		return id;
	}

	void destroy_entity(Entity entity) {
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		m_signatures[entity].reset();

		// Put the destroyed ID at the back of the queue
		m_available_entities.push(entity);
		--m_living_entities_count;
	}

	void set_signature(Entity entity, Signature signature) {
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		m_signatures[entity] = signature;
	}

	Signature get_signature(Entity entity) {
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return m_signatures[entity];
	}

private:
	// Queue of unused entity IDs
	std::queue<Entity> m_available_entities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> m_signatures{};

	// Total living entities - used to keep limits on how many exist
	uint32_t m_living_entities_count{};
};

#endif