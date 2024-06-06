#include <generated/systems/producer_systems/ai_system.h>

#include <generated/events/move_event.h>
void AISystem::for_every_entity(
	EntityHandle entity,
    VelocityComponent& velocity) {
	velocity.final_destination = std::get<0>(m_game->components->unpack<BoundaryComponent>(m_game->player))->hitbox.getPosition();
	entity.receive_event(MoveEvent());
}

