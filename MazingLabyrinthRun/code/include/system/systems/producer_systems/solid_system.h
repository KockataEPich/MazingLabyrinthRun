#ifndef SOLID_SYSTEM_HEADER
#define SOLID_SYSTEM_HEADER

#include <components/data_components/facing_side_component.h>
#include <components/data_components/speed_component.h>
#include <components/data_components/transform_component.h>
#include <components/data_components/solid_component.h>

#include <components/event_components/collision_component.h>

#include <world/world.h>
#include <system/system.h>
class Solid : public ProducerSystem {
public:
	Solid() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SolidComponent>();
	}
	std::vector<Entity>& get_registered_entities() { return m_registered_entities; };
};

#endif