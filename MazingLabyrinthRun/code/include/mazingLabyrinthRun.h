#include "window/gameWindow.h"

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
};