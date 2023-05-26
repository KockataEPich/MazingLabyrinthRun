#include <system/systems/producer_systems/display_healthpoints_system.h>

#include <component_base/component_handle.h>
#include <world/world.h>
#include <SFML/Graphics/Text.hpp>

void DisplayHealthpoints::update() {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<HealthPointsComponent> health_points;

		m_parent_world->unpack(entity, transform, health_points);

		sf::Text text;
		text.setFont(m_font);
		text.setString(std::to_string(health_points->m_health) + "/50");
		text.setCharacterSize(15);

		auto position = transform->m_position;
		position.y -= 50;
		position.x -= 20;
		text.setPosition(position);
		m_render_window.draw(text);
	}
}
