#include <generated/systems/producer_systems/display_health_system.h>
void DisplayHealthSystem::for_every_entity(Entity entity,
										   TransformComponent& transform,
										   HealthPointsComponent& health_points){
	sf::Text text;
	text.setFont(m_font);
	text.setString(std::to_string(health_points.health) + "/50");
	text.setCharacterSize(15);

	auto position = transform.position;

	position.y -= 50;
	position.x -= 20;
	text.setPosition(position);
	m_render_window.draw(text);
}

void DisplayHealthSystem::init() {
	if (!m_font.loadFromFile("resources/fonts/Raleway-Black.ttf")) throw;
}
