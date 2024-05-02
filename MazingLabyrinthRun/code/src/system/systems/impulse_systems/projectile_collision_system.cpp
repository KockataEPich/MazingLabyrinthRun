#include <generated/systems/impulse_systems/projectile_collision_system.h>
#include <generated/components/basic_components/flash_white_component.h>

void ProjectileCollisionSystem::clash_entities(
        EntityHandle initiator,
        
        EntityHandle victim,
		HealthPointsComponent& victim_health_points,

		const CollisionInfo& collision_info
    ){
	m_game->destroy_entity(initiator.entity);
	victim_health_points.health -= 15;
	if (victim_health_points.health <= 0) 
		m_game->destroy_entity(victim.entity);

	victim.add_event_components<FlashWhiteComponent>();
}