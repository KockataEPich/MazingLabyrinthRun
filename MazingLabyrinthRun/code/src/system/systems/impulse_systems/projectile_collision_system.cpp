#include <generated/systems/impulse_systems/projectile_collision_system.h>
void ProjectileCollisionSystem::clash_entities(
        Entity initiator,
        
        Entity victim,
		HealthPointsComponent& victim_health_points
    ){
	m_parent_world->destroy_entity(initiator);
	victim_health_points.health -= 1;
	if (victim_health_points.health < 0) 
		m_parent_world->destroy_entity(victim);
}