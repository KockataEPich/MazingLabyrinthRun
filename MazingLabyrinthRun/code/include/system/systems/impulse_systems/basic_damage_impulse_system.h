#ifndef BASIC_DAMAGE_IMPULSE_SYSTEM_HEADER
#define BASIC_DAMAGE_IMPULSE_SYSTEM_HEADER


#include <components/impulse_components/needle/basic_attack_needle.h>
#include <components/data_components/health_points_component.h>

#include <world/world.h>
#include <system/system.h>

class BasicDamageImpulseExchange : public ImpulseSystem {
public:
	BasicDamageImpulseExchange() {
		m_signature.add_component<BasicAttackNeedle>();

		m_signature_of_victim.add_component<HealthPointsComponent>();
	}
	void exchange_impulse(const Entity& initiator, const Entity& victim) override;
};

#endif