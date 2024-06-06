#include <generated/systems/producer_systems/projectile_system.h>
#include <generated/events/move_event.h>

void ProjectileSystem::for_every_entity(
        EntityHandle entity,
        VelocityComponent& velocity
    ){
	entity.receive_event(MoveEvent());
}