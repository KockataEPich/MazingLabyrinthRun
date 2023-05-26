#ifndef DISPLAY_HITPOINTS_SYSTEM_HEADER
#define DISPLAY_HITPOINTS_SYSTEM_HEADER

#include <components/data_components/transform_component.h>
#include <components/data_components/health_points_component.h>
#include <window/game_window.h>
#include <system/system.h>

class DisplayHealthpoints : public ProducerSystem {
public:
	DisplayHealthpoints(GameWindow& render_window) : m_render_window{render_window} {
		m_signature.add_component<TransformComponent>().add_component<HealthPointsComponent>();
		if (!m_font.loadFromFile("resources/fonts/Raleway-Black.ttf")) throw;
	}
	void update() override;

private:
	GameWindow& m_render_window;
	sf::Font m_font;

};

#endif