// ################## THIS FILE IS GENERATED ##################
#ifndef UPDATE_CROSSHAIR_POSITION_SYSTEM_HEADER
#define UPDATE_CROSSHAIR_POSITION_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>
#include <window/game_window.h>

#include <generated/components/data_components/transform_component.h>
#include <generated/components/basic_components/mouse_component.h>
#include <generated/components/data_components/boundary_component.h>

class UpdateCrosshairPositionSystem : public ProducerSystem {
public:
	UpdateCrosshairPositionSystem(
		GameWindow& game_window) : 
		m_game_window{game_window}{

		m_signature
			.add_component<TransformComponent>()
			.add_component<MouseComponent>()
			.add_component<BoundaryComponent>();
	}
	void update() override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<TransformComponent> transform;
			ComponentHandle<BoundaryComponent> boundary;
			m_parent_world->unpack(entity,
				transform,
				boundary);

			for_every_entity(entity,
				*transform,
				*boundary);
		}
	}
private:
	GameWindow& m_game_window;

	void for_every_entity(
		Entity entity,
		TransformComponent& transform,
		BoundaryComponent& boundary);

};
#endif