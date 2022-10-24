#ifndef MAZING_LABYRINTH_RUN_HEADER_H
#define MAZING_LABYRINTH_RUN_HEADER_H

#include "window/game_window.h"
#include "world/world.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

class MazingLabyrinthRun {
public:
	MazingLabyrinthRun();
	void start_game();

private:
	std::unique_ptr<World> m_world;
	GameWindow m_window;

	sf::View m_camera;
	sf::Clock m_clock;
	sf::Time m_elapsed;

	float m_deltaTime;

	void handle_input();
	void update();
	void render();
	void restart_clock() { m_elapsed = m_clock.restart(); }
	void initialize_game();

	sf::Texture tile_texture;
	std::vector<sf::Sprite> grass_lands;

	sf::Sprite* m_player_sprite;
};

#endif // !MAZING_LABYRINTH_RUN_HEADER_H
