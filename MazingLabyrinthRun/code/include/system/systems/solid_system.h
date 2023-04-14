#ifndef SOLID_SYSTEM_HEADER
#define SOLID_SYSTEM_HEADER

#include "../../components/facing_side_component.h"
#include "../../components/speed_component.h"
#include "../../components/transform_component.h"
#include "../../components/solid_component.h"
#include "../../components/collision_component.h"

#include "../../world/world.h"
#include "../system.h"
class Solid : public ProducerSystem {
public:
	Solid() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SolidComponent>();
	}
	std::vector<Entity>& get_registered_entities() { return m_registered_entities; };
};

#endif