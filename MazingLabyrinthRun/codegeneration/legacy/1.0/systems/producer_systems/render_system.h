// ################## THIS FILE IS GENERATED ##################
#ifndef RENDER_SYSTEM_HEADER
#define RENDER_SYSTEM_HEADER

#include <world/world.h>
#include <window/game_window.h>

#include <generated/components/data_components/sprite_component.h>
#include <generated/components/data_components/elevation_level_component.h>

class RenderSystem : public ProducerSystem {
public:
	RenderSystem() {
		m_signature
			.add_component<SpriteComponent>()
			.add_component<ElevationLevelComponent>();
	}
	void register_entity(Entity const& entity) override;
	void unregister_entity(Entity const& entity) override;
	void update() override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<SpriteComponent> sprite;
			ComponentHandle<ElevationLevelComponent> elevation_level;
			m_parent_world->unpack(entity,
				sprite,
				elevation_level);

			for_every_entry(Entity entity,
				*sprite,
				*elevation_level);
		}
	}
private:
	GameWindow& m_render_window;
	std::vector<std::pair<sf::Sprite*, Entity>> m_level_one_sprites;
	std::vector<std::pair<sf::Sprite*, Entity>> m_level_two_sprites;
	std::vector<std::pair<sf::Sprite*, Entity>> m_level_UI_sprites;

	void for_every_entity(Entity entity,
		SpriteComponent& sprite,
		ElevationLevelComponent& elevation_level);

	void draw_level(std::vector<std::pair<sf::Sprite*, Entity>>& sprites, bool draw_hitbox = false);
	std::vector<std::pair<sf::Sprite*, Entity>>& get_level_vector(ElevationLevel level);
};
#endif