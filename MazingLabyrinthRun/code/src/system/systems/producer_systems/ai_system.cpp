#include <generated/systems/producer_systems/ai_system.h>

#include <generated/components/basic_components/move_component.h>
void AISystem::for_every_entity(
	EntityHandle entity,
    TransformComponent& transform,
    SpeedComponent& speed,
    FacingSideComponent& facing_side,
    VelocityComponent& velocity) {
	velocity.final_destination = std::get<0>(m_game->components->unpack<BoundaryComponent>(0))->hitbox.getPosition() + std::get<0>(m_game->components->unpack<BoundaryComponent>(0))->hitbox.getSize() * 0.5f;
	entity.add_event_components<MoveComponent>();
}

