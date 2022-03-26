#ifndef MAZING_LABYRINTH_RUN_HEADER_H
#define MAZING_LABYRINTH_RUN_HEADER_H

#include "tile/tileFactory.h"
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
	TextureManager m_textureManager;
	TileFactory m_tileFactory{m_textureManager};
	WorldObjectHolder m_worldObjectHolder;
	Player m_player;

	sf::View m_camera;

	void moveBall();
	void initialize_game();
};

#endif // !MAZING_LABYRINTH_RUN_HEADER_H
