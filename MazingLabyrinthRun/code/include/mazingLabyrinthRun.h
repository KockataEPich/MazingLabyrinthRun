#ifndef MAZING_LABYRINTH_RUN_HEADER_H
#define MAZING_LABYRINTH_RUN_HEADER_H

#include "tile/tileFactory.h"
#include "window/gameWindow.h"
#include "world/spriteHolder.h"

#include <SFML/Graphics/Texture.hpp>

class MazingLabyrinthRun {
public:
	MazingLabyrinthRun();

	void start_game();

	void handleInput();
	void update();
	void render();
	GameWindow& getWindow() { return m_window; };

private:
	void moveBall();
	GameWindow m_window;
	TextureManager m_textureManager;
	TileFactory m_tileFactory{m_textureManager};
	SpriteHolder m_spriteHolder;

	sf::Sprite m_player;
	sf::Texture m_player_texture;
};

#endif // !MAZING_LABYRINTH_RUN_HEADER_H
