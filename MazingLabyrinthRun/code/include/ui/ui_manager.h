#ifndef  UI_MANAGER_HEADER
#define UI_MANAGER_HEADER

#include <ui/health_bar.h>
class Game;
class UIManager {
public:
	UIManager(Game* game) : m_game{game} {};

	void init();
	void update_ui();
	void render_ui();

private:
	Game* m_game;
	HealthBar m_player_health_bar;
};

#endif  // ! UI_MANAGER_HEADER
