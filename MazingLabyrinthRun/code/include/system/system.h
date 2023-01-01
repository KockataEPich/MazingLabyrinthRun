#ifndef BASE_SYSTEM_HEADER
#define BASE_SYSTEM_HEADER

#include "../component_base/component_mask.h"
#include "../entity_base/entity.h"

#include <bitset>
#include <vector>

class World;

//remove_entity_from_

class System {
public:
	System() = default;
	virtual ~System() = default;
	System(const System&) = default;
	System& operator=(const System&) = default;
	System(System&&) = default;
	System& operator=(System&&) = default;
	virtual void init(){};
	virtual void update(float dt){};
	virtual void render(){};

	virtual void unregister_entity(Entity const& entity);

	void register_world(World* world) { m_parent_world = world; }
	virtual void register_entity(Entity const& entity) { m_registered_entities.push_back(entity); }
	ComponentMask get_signature() { return m_signature; }

protected:
	std::vector<Entity> m_registered_entities;
	World* m_parent_world;
	ComponentMask m_signature;
};

#endif
