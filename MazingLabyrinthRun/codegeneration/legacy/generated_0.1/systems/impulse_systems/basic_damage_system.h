// ################## THIS FILE IS GENERATED ##################
#ifndef BASIC_DAMAGE_SYSTEM_HEADER
#define BASIC_DAMAGE_SYSTEM_HEADER

#include <world/world.h>

#include <generated/components/basic_components/basic_attack_needle_component.h>
#include <generated/components/data_components/health_points_component.h>

class BasicDamageSystem : public ImpulseSystem {
public:
	BasicDamageSystem() {
		m_signature
			.add_component<BasicAttackNeedleComponent>();

		m_signature_of_victim
			.add_component<HealthPointsComponent>();
	}
	void exchange_impulse(const Entity& initiator, const Entity& victim) override {

		ComponentHandle<HealthPointsComponent> health_points;
		m_parent_world->unpack(victim,
			health_points);


		do_impulse(initiator,
			victim,
			*health_points);
	}
private:

	void do_impulse(Entity initiator,
		Entity victim,
		HealthPointsComponent& victim_health_points);


};
#endif