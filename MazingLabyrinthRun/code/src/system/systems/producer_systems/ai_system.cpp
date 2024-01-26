#include <generated/systems/producer_systems/ai_system.h>

#include <generated/components/basic_components/move_component.h>
void AISystem::for_every_entity(
	Entity entity,
    TransformComponent& transform,
    SpeedComponent& speed,
    FacingSideComponent& facing_side,
    TargetForDirectionComponent& target_for_direction) {

	target_for_direction.target_position = m_game->world->get_player_sprite().getPosition();
	m_game->add_event_component(entity, std::make_unique<MoveComponent>());
}

