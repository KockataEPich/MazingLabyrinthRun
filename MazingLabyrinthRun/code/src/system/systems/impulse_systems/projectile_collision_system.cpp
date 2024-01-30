#include <generated/systems/impulse_systems/projectile_collision_system.h>
void ProjectileCollisionSystem::clash_entities(
        EntityHandle initiator,
        
        EntityHandle victim,
		HealthPointsComponent& victim_health_points
    ){
	m_game->destroy_entity(initiator.entity);
	victim_health_points.health -= 1;
	if (victim_health_points.health <= 0) 
		m_game->destroy_entity(victim.entity);
}