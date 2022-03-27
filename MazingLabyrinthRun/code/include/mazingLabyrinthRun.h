#ifndef MAZING_LABYRINTH_RUN_HEADER_H
#define MAZING_LABYRINTH_RUN_HEADER_H

#include "window/gameWindow.h"
#include "world/worldObjectHolder.h"
#include "player/player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

class MazingLabyrinthRun {
public:
	MazingLabyrinthRun();

	void start_game();

	void handleInput();
	void update();
	void render();
	GameWindow& getWindow() { return m_window; };

private:
	GameWindow m_window;
	WorldObjectHolder m_worldObjectHolder;
	Player m_player;

	sf::View m_camera;
	void initialize_game();
};

#endif // !MAZING_LABYRINTH_RUN_HEADER_H
