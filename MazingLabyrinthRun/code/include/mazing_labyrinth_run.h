#ifndef MAZING_LABYRINTH_RUN_HEADER_H
#define MAZING_LABYRINTH_RUN_HEADER_H

#include <window/game_window.h>
#include <game.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

class MazingLabyrinthRun {
public:
	MazingLabyrinthRun();
	void start_game();

private:
	std::unique_ptr<Game> m_game;
	GameWindow m_window;

	sf::View m_camera;
	sf::Clock m_clock;
	sf::Time m_elapsed;

	float m_delta_time;

	void handle_input();
	void update();
	void render();
	void restart_clock() { m_elapsed = m_clock.restart(); }
	void initialize_game();

	sf::Sprite* m_player_sprite;
};

#endif // !MAZING_LABYRINTH_RUN_HEADER_H
