#ifndef BASE_SYSTEM_HEADER
#define BASE_SYSTEM_HEADER

#include "../component_base/component_mask.h"
#include "../entity_base/entity.h"


#include <bitset>
#include <vector>

class World;

class System {
public:
	System() = default;
	virtual ~System() = default;
	System(const System&) = default;
	System& operator=(const System&) = default;
	System(System&&) = default;
	System& operator=(System&&) = default;

	ComponentMask get_signature() { return m_signature; }
	void register_world(World* world) { m_parent_world = world; }
	virtual void init(){};

protected:
	World* m_parent_world;
	ComponentMask m_signature;
};

class EntityTrackerSystem : public System {
public:
	EntityTrackerSystem() = default;
	virtual void unregister_entity(Entity const& entity) { 
		std::erase(m_registered_entities, entity); 
	}
	virtual void register_entity(Entity const& entity) { m_registered_entities.push_back(entity); }

protected:
	std::vector<Entity> m_registered_entities;
};


class ProducerSystem : public EntityTrackerSystem {
public:
	void update_in_ticks() {
		m_tick_accumulator++;
		if (m_tick_accumulator == tick_frequency()) {
			update();
			m_tick_accumulator--;
		}
	}

	virtual void update(){};

protected:
	
	float m_tick_accumulator = 0;
	virtual const int tick_frequency() { return 1; };
};

class ReactSystem : public System {
public:
	virtual void react(Entity const entity) {}
};

class RenderSystem : public EntityTrackerSystem {
public:
	virtual void render() {}
};


class ImpulseSystem : public System {
public:
	virtual void exchange_impulse(const Entity initiator, const Entity victim) {}

	ComponentMask get_signature_of_victim() { return m_signature_of_victim; }

protected:
	ComponentMask m_signature_of_victim;
};
#endif
