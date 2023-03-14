#ifndef SYSTEM_SEQUENCE_WRAPPER_HEADER
#define SYSTEM_SEQUENCE_WRAPPER_HEADER

#include "../component_base/component_mask.h"
#include "../entity_base/entity.h"

#include <bitset>
#include <vector>

const float base_system_tick_frequency = 0.015;

class World;

class SystemSequenceWrapper {
public:

protected:
	std::vector<Entity> m_registered_entities;
	World* m_parent_world;
	ComponentMask m_signature;
	float m_accumulator = 0;

	virtual void update(float dt){};
	virtual const float tick_frequency() { return 1.0f; };
};
#endif
