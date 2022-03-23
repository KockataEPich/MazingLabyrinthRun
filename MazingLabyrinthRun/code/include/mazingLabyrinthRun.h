#include "window/gameWindow.h"
#include "tile/tileFactory.h"


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
};