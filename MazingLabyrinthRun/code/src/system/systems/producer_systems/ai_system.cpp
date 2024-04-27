#include <generated/systems/producer_systems/ai_system.h>

#include <generated/components/basic_components/move_component.h>
void AISystem::for_every_entity(
	EntityHandle entity,
    VelocityComponent& velocity) {
	velocity.final_destination = std::get<0>(m_game->components->unpack<BoundaryComponent>(m_game->player))->hitbox.getPosition();
	entity.add_event_components<MoveComponent>();
}

