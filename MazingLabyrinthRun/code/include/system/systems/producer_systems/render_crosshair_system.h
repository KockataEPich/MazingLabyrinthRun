#ifndef UPDATE_CROSSHAIR_POSITION_SYSTEM_HEADER
#define UPDATE_CROSSHAIR_POSITION_SYSTEM_HEADER

#include <components/data_components/mouse_component.h>
#include <components/data_components/transform_component.h>
#include <components/data_components/boundary_component.h>
#include <system/system.h>
#include <window/game_window.h>
#include <world/world.h>

#include <SFML/Graphics/View.hpp>

class UpdateCrosshairPosition : public ProducerSystem {
public:
	UpdateCrosshairPosition(GameWindow& game_window) : m_game_window{game_window} {
		m_signature.add_component<TransformComponent>()
			.add_component<MouseComponent>()
			.add_component<BoundaryComponent>();
	}

	void update() override;

private:
	GameWindow& m_game_window;
};

#endif