// ################## THIS FILE IS GENERATED ##################
#ifndef DISPLAY_HEALTH_SYSTEM_HEADER
#define DISPLAY_HEALTH_SYSTEM_HEADER

#include <world/world.h>
#include <window/game_window.h>

#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/health_points_component.h>

class DisplayHealthSystem : public ProducerSystem {
public:
	DisplayHealthSystem(
		GameWindow& game_window) : 
		m_game_window{game_window}{

		m_signature
			.add_component<TransformComponent>()
			.add_component<HealthPointsComponent>();
	}
	void init() override;
	void update() override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<TransformComponent> transform;
			ComponentHandle<HealthPointsComponent> health_points;
			m_parent_world->unpack(entity,
				transform,
				health_points);

			for_every_entry(Entity entity,
				*transform,
				*health_points);
		}
	}
private:
	GameWindow& m_game_window;
	sf::Font m_font;

	void for_every_entity(Entity entity,
		TransformComponent& transform,
		HealthPointsComponent& health_points);

};
#endif