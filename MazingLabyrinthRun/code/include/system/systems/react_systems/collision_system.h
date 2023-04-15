#ifndef COLLISION_SYSTEM_HEADER
#define COLLISION_SYSTEM_HEADER

#include <components/data_components/facing_side_component.h>
#include <components/data_components/speed_component.h>
#include <components/data_components/transform_component.h>
#include <components/data_components/solid_component.h>
#include <components/event_components/collision_component.h>

#include <world/world.h>
#include <system/system.h>
#include <system/systems/producer_systems/solid_system.h>
class Collision : public ReactSystem {
public:
	Collision(Solid* solid_system) : m_solid_system{solid_system} {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpeedComponent>();
		m_signature.add_component<FacingSideComponent>();
		m_signature.add_component<SolidComponent>();
		m_signature.add_component<CollisionComponent>();
	}
	void react(Entity const& entity);

private:
	Solid* m_solid_system;
};

#endif