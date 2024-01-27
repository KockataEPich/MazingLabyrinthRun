#include <generated/systems/producer_systems/projectile_system.h>
#include <generated/components/basic_components/move_component.h>


void ProjectileSystem::for_every_entity(
        Entity entity,
        TargetForDirectionComponent& target_for_direction
    ){
	m_game->add_event_components<MoveComponent>(entity);
}