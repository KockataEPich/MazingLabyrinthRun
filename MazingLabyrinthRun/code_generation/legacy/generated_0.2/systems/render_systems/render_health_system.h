// ################## THIS FILE IS GENERATED ##################
#ifndef RENDER_HEALTH_SYSTEM_HEADER
#define RENDER_HEALTH_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>
#include <window/game_window.h>

#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/health_points_component.h>

class RenderHealthSystem : public RenderSystem {
public:
	RenderHealthSystem(
		GameWindow& render_window) : 
		m_render_window{render_window}{

		m_signature
			.add_component<TransformComponent>()
			.add_component<HealthPointsComponent>();
	}
	void init() override;
	void render() override;
private:
	GameWindow& m_render_window;
	sf::Font m_font;

};
#endif