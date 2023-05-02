#ifndef BASIC_COLLISION_IMPULSE_EXCHANGE_SYSTEM_HEADER
#define BASIC_COLLISION_IMPULSE_EXCHANGE_SYSTEM_HEADER

#include <components/data_components/facing_side_component.h>
#include <components/data_components/speed_component.h>
#include <components/data_components/transform_component.h>
#include <components/data_components/solid_component.h>

#include <components/impulse_components/armor/default_collision_armor.h>

#include <world/world.h>
#include <system/system.h>

class BasicCollisionImpulseExchange : public ImpulseSystem {
public:
	BasicCollisionImpulseExchange() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpeedComponent>();
		m_signature.add_component<FacingSideComponent>();
		m_signature.add_component<SolidComponent>();

		m_signature_of_victim.add_component<SolidComponent>();
		m_signature_of_victim.add_component<DefaultCollisionArmor>();
	}
	void exchange_impulse(const Entity& initiator, const Entity& victim) override;
};

#endif