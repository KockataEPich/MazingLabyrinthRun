#include <generated/systems/producer_systems/projectile_system.h>
#include <generated/components/basic_components/move_component.h>


void ProjectileSystem::for_every_entity(
        EntityHandle entity,
        VelocityComponent& velocity
    ){
	entity.add_event_components<MoveComponent>();
}