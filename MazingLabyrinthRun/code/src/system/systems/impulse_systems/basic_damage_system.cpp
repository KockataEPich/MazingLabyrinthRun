#include <generated/systems/impulse_systems/basic_damage_system.h>
void BasicDamageSystem::do_impulse(
	Entity initiator,
	Entity victim,
	HealthPointsComponent& victim_health_points){ 
	victim_health_points.health -= 5;
}


