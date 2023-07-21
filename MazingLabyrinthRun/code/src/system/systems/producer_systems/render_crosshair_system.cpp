#include <component_base/component_handle.h>
#include <system/systems/producer_systems/render_crosshair_system.h>
void UpdateCrosshairPosition::update() {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<BoundaryComponent> boundary;

		m_parent_world->unpack(entity, transform, boundary);

		auto pos = sf::Mouse::getPosition(m_game_window.as_sfml_window());
		sf::Vector2f worldPos = m_game_window.as_sfml_window().mapPixelToCoords(pos);
		transform->m_position = {worldPos.x, worldPos.y};

		boundary->m_hitbox = get_hitbox_based_on_transform_component(*transform);
	}
}