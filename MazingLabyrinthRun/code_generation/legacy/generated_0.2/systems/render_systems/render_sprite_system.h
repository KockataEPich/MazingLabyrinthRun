// ################## THIS FILE IS GENERATED ##################
#ifndef RENDER_SPRITE_SYSTEM_HEADER
#define RENDER_SPRITE_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>
#include <window/game_window.h>

#include <generated/components/data_components/sprite_component.h>
#include <generated/components/data_components/elevation_level_component.h>

class RenderSpriteSystem : public RenderSystem {
public:
	RenderSpriteSystem(
		GameWindow& render_window) : 
		m_render_window{render_window}{

		m_signature
			.add_component<SpriteComponent>()
			.add_component<ElevationLevelComponent>();
	}
	void register_entity(Entity const& entity) override;
	void unregister_entity(Entity const& entity) override;
	void render() override;
private:
	GameWindow& m_render_window;
	std::vector<std::pair<sf::Sprite*, Entity>> m_level_one_sprites;
	std::vector<std::pair<sf::Sprite*, Entity>> m_level_two_sprites;
	std::vector<std::pair<sf::Sprite*, Entity>> m_level_UI_sprites;

	void draw_level(std::vector<std::pair<sf::Sprite*, Entity>>& sprites, bool draw_hitbox = false);
	std::vector<std::pair<sf::Sprite*, Entity>>& get_level_vector(ElevationLevel level);
};
#endif