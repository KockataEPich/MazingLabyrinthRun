#include <generated/systems/producer_systems/ai_system.h>

#include <generated/components/basic_components/move_component.h>
void AISystem::for_every_entity(
	EntityHandle entity,
    TransformComponent& transform,
    SpeedComponent& speed,
    FacingSideComponent& facing_side,
    VelocityComponent& velocity) {

	velocity.target_point = m_game->world->get_player_sprite().getPosition();
	entity.add_event_components<MoveComponent>();
}

