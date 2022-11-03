#ifndef RENDER_SYSTEM_HEADER
#define RENDER_SYSTEM_HEADER

#include "../../components/sprite_component.h"
#include "../../components/elevation_component.h"
#include "../../window/game_window.h"
#include "../../world/world.h"
#include "../system.h"

class Render : public System {
public:
	Render(GameWindow& render_window) : m_render_window{render_window} {
		m_signature.add_component<SpriteComponent>();
		m_signature.add_component<ElevationLevelComponent>();
	}
	void register_entity(Entity const& entity) override;
	void unregister_entity(Entity const& entity) override;
	void render() override;

private:
	std::vector<std::pair<sf::Sprite*, Entity>> level_one_sprites;
	std::vector<std::pair<sf::Sprite*, Entity>> level_two_sprites;
	GameWindow& m_render_window;

	void draw_level(std::vector<std::pair<sf::Sprite*, Entity>>& sprites);
};

#endif