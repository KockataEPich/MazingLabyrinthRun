#include <generated/systems/react_systems/update_crosshair_position_system.h>
void UpdateCrosshairPositionSystem::react_on_entity(
        EntityHandle entity,
        TransformComponent& transform,
		BoundaryComponent& boundary,
		SpriteComponent& sprite
    ){
	auto pos = sf::Mouse::getPosition(m_game->window->as_sfml_window());
	sf::Vector2f worldPos = m_game->window->as_sfml_window().mapPixelToCoords(pos);
	transform.position = {worldPos.x, worldPos.y};
	entity.add_event_components<UpdateBoundaryFromTransformComponent>();
	sprite.sprite.setPosition(transform.position);
	sprite.sprite.setScale(transform.scale);
}