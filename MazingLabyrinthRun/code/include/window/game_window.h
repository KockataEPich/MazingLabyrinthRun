#ifndef GAME_WINDOW_HEADER_H
#define GAME_WINDOW_HEADER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameWindow {
public:
	GameWindow();
	GameWindow(const std::string& title, const sf::Vector2u& size);
	~GameWindow();

	void begin_draw();
	void end_draw();
	void update();
	bool is_done();
	bool is_full_screen();
	sf::Vector2u get_window_size();
	void setView(sf::View& view);

	void toggle_fullscreen();
	void draw(sf::Drawable& drawable);

private:
	sf::RenderWindow m_game_window;
	sf::Vector2u m_window_size;
	std::string m_window_title;
	bool m_is_done;
	bool m_is_fullscreen;

	void setup(const std::string& title, const sf::Vector2u& size);
	void destroy();
	void create();
};

#endif