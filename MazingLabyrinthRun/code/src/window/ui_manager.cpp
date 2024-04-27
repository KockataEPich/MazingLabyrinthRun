#include <ui/ui_manager.h>
#include <generated/components/data_components/health_points_component.h>
#include <game.h>

void UIManager::update_ui() {

}

void UIManager::render_ui() {
	sf::RectangleShape rectangle({200, 50});
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	auto position_x = m_game->window->as_sfml_window().getView().getCenter().x -
	                  m_game->window->as_sfml_window().getView().getSize().x * 0.48f;
	auto position_y = m_game->window->as_sfml_window().getView().getCenter().y -
	                  m_game->window->as_sfml_window().getView().getSize().y * 0.48f;
	rectangle.setPosition({(float)position_x, (float)position_y});
	
	sf::Font font;
	font.loadFromFile("resources/fonts/Raleway-Black.ttf");

	auto player_hp = std::get<0>(m_game->components->unpack<HealthPointsComponent>(m_game->player))->health;
	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(player_hp) + "/50");
	text.setCharacterSize(30);

	text.setOrigin(text.getLocalBounds().width * 0.5f, text.getLocalBounds().height * 0.5f);
	text.setPosition(rectangle.getPosition() + rectangle.getSize() * 0.5f);

	float health_percentage = (float)player_hp / 50; 
	int left_of_rectangle = rectangle.getPosition().x + rectangle.getSize().x * health_percentage;
	int width_of_rectangle = rectangle.getSize().x - rectangle.getSize().x * health_percentage;

	sf::RectangleShape health_removal({(float)width_of_rectangle, rectangle.getSize().y});
	health_removal.setFillColor(sf::Color::Black);
	health_removal.setPosition({(float)left_of_rectangle, (float)position_y});

	m_game->window->draw(rectangle);
	m_game->window->draw(health_removal);
	m_game->window->draw(text);
}

void UIManager::init() {}