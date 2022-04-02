#ifndef MAZING_LABYRINTH_RUN_HEADER_H
#define MAZING_LABYRINTH_RUN_HEADER_H

#include "window/gameWindow.h"
//#include "world/worldObjectHolder.h"
#include "player/player.h"
#include "resource/animation.h"
#include "resource/textureHolder.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

class MazingLabyrinthRun {
public:
	MazingLabyrinthRun();
	void start_game();

private:
	GameWindow m_window;
	//WorldObjectHolder m_worldObjectHolder;
	TextureHolder<PlayerTextures> holder{allPlayerTextures};
	Animation<PlayerTextures> animation{holder, PlayerTextures::down};
	Player m_player{animation};
	sf::View m_camera;
	sf::Clock m_clock;
	sf::Time m_elapsed;

	float m_deltaTime;

	void handleInput();
	void update();
	void render();
	GameWindow& getWindow() { return m_window; };
	sf::Time MazingLabyrinthRun::getElapsed() { return m_elapsed; }
	void MazingLabyrinthRun::restartClock() { m_elapsed = m_clock.restart(); }
	void initialize_game();
};

#endif // !MAZING_LABYRINTH_RUN_HEADER_H
