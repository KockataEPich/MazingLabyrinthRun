#include <generated/systems/render_systems/render_health_system.h>

void RenderHealthSystem::render() {
	for (auto& entity : m_registered_entities) {
		auto [transform, health_points] = m_game->components->unpack<TransformComponent, HealthPointsComponent>(entity);

		sf::Text text;
		text.setFont(m_font);
		text.setString(std::to_string(health_points->health) + "/50");
		text.setCharacterSize(20);

		auto position = transform->position;

		position.y -= 100;
		position.x -= 20;
		text.setPosition(position);
		m_render_window.draw(text);
	}
}

void RenderHealthSystem::init() { if (!m_font.loadFromFile("resources/fonts/Raleway-Black.ttf")) throw; }
