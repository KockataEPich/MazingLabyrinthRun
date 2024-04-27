#ifndef  UI_MANAGER_HEADER
#define UI_MANAGER_HEADER

class Game;
class UIManager {
public:
	UIManager(Game* game) : m_game{game} {};

	void init();
	void update_ui();
	void render_ui();

private:
	Game* m_game;
};

#endif  // ! UI_MANAGER_HEADER
