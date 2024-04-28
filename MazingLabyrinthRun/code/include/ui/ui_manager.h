#ifndef  UI_MANAGER_HEADER
#define UI_MANAGER_HEADER

#include <ui/health_bar.h>
#include <ui/ability_list.h>
class Game;
class UIManager {
public:
	UIManager(Game* game) : m_game{game} {};

	void init();
	void update_ui();
	void render_ui();

private:
	Game* m_game;
	HealthBar m_health_bar;
	AbilityList m_ability_list;
};

#endif  // ! UI_MANAGER_HEADER
