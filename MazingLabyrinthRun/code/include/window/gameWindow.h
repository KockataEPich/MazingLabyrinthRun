#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>

class GameWindow {
public:
	GameWindow();
	GameWindow(const std::string& title, const sf::Vector2u& size);
	~GameWindow();

	void beginDraw(); 
	void endDraw(); 
	void update();
	bool isDone();
	bool isFullscreen();
	sf::Vector2u getWindowSize();

	void toggleFullscreen();
	void draw(sf::Drawable& drawable);

private:
	sf::RenderWindow m_gameWindow;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;

	void setup(const std::string& title, const sf::Vector2u& size);
	void destroy();
	void create();
};