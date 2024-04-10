#include <generated/systems/producer_systems/update_crosshair_position_system.h>
#include <utils/component_utils.h>

void UpdateCrosshairPositionSystem::for_every_entity(
	EntityHandle entity,
	TransformComponent& transform,
	BoundaryComponent& boundary){ 

	auto pos = sf::Mouse::getPosition(m_game_window.as_sfml_window());
	sf::Vector2f worldPos = m_game_window.as_sfml_window().mapPixelToCoords(pos);
	transform.position = {worldPos.x, worldPos.y};
	entity.add_event_components<UpdateBoundaryFromTransformComponent>();

	auto potential_overlaps = m_game->quad_tree->get_potential_collisions(boundary.hitbox, {0, 0});
	for (auto overlapping_entity : potential_overlaps) { 
		auto overlapping_boundary = std::get<0>(
			m_game->components->unpack<BoundaryComponent>(overlapping_entity))->hitbox;

		if (boundary.hitbox.intersects(overlapping_boundary))
			m_game->systems->exchange_impulses(entity.entity, overlapping_entity, {});
	}
}

