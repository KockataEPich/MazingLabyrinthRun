#ifndef COLLISION_RESOLUTION_SYSTEM_HEADER
#define COLLISION_RESOLUTION_SYSTEM_HEADER

#include <components/data_components/facing_side_component.h>
#include <components/data_components/speed_component.h>
#include <components/data_components/transform_component.h>
#include <components/data_components/impulse_component.h>
#include <components/data_components/solid_component.h>

#include <components/event_components/resolve_collision_event_component.h>
#include <components/event_components/receive_impulse_event_component.h>
#include <components/impulse_components/colide.h>



#include <world/world.h>
#include <system/system.h>

class CollisionResolution : public ImpulseSystem {
public:
	CollisionResolution() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpeedComponent>();
		m_signature.add_component<FacingSideComponent>();

		m_signature_of_victim.add_component<SolidComponent>();
	}
	void exchange_impulse(const Entity& initiator, const Entity& victim) override;
};

#endif