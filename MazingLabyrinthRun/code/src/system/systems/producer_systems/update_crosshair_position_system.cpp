#include <generated/systems/producer_systems/update_crosshair_position_system.h>
#include <utils/component_utils.h>

void UpdateCrosshairPositionSystem::for_every_entity(
	Entity entity,
	TransformComponent& transform,
	BoundaryComponent& boundary){ 

	auto pos = sf::Mouse::getPosition(m_game_window.as_sfml_window());
	sf::Vector2f worldPos = m_game_window.as_sfml_window().mapPixelToCoords(pos);
	transform.position = {worldPos.x, worldPos.y};

	boundary.hitbox = get_hitbox_based_on_transform_component(transform);
}

