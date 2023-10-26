#include <generated/systems/render_systems/render_health_system.h>

void RenderHealthSystem::render() {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<HealthPointsComponent> health_points;
		m_parent_world->unpack(entity, transform, health_points);

		sf::Text text;
		text.setFont(m_font);
		text.setString(std::to_string(health_points->health) + "/50");
		text.setCharacterSize(15);

		auto position = transform->position;

		position.y -= 50;
		position.x -= 20;
		text.setPosition(position);
		m_render_window.draw(text);
	}
}

void RenderHealthSystem::init() {
	if (!m_font.loadFromFile("resources/fonts/Raleway-Black.ttf")) throw;
}
