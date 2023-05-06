#include <system/systems/impulse_systems/basic_damage_impulse_system.h>
#include <component_base/component_handle.h>

void BasicDamageImpulseExchange::exchange_impulse(const Entity& initiator, const Entity& victim) {
	ComponentHandle<HealthPointsComponent> health_points;

	m_parent_world->unpack(victim, health_points);
	health_points->m_health -= 5;
} 