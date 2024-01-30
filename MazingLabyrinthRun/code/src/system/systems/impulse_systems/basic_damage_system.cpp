#include <generated/systems/impulse_systems/basic_damage_system.h>
void BasicDamageSystem::clash_entities(
	EntityHandle initiator,
	EntityHandle victim,
	HealthPointsComponent& victim_health_points){ 
	victim_health_points.health -= 5;
}


