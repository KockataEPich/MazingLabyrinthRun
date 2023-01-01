#include "../include/window/game_window.h"

GameWindow::GameWindow() { setup("MazingLabyrinthRun", sf::Vector2u(1280, 720)); }
GameWindow::GameWindow(const std::string& title, const sf::Vector2u& size) { setup(title, size); }

GameWindow::~GameWindow() { destroy(); }

void GameWindow::setup(const std::string& title, const sf::Vector2u& size) {
	m_window_title = title;
	m_window_size = size;
	m_is_fullscreen = false;
	m_is_done = false;
	create();
}

void GameWindow::create() {
	auto style = m_is_fullscreen ? sf::Style::Fullscreen : sf::Style::Close;
	m_game_window.create({m_window_size.x, m_window_size.y, 32}, m_window_title, style);

	m_game_window.setFramerateLimit(60);
}

void GameWindow::destroy() { m_game_window.close(); }

bool GameWindow::is_done() { return m_is_done; }
bool GameWindow::is_full_screen() { return m_is_fullscreen; }
sf::Vector2u GameWindow::get_window_size() { return m_window_size; }
void GameWindow::setView(sf::View& view) { return m_game_window.setView(view); }

void GameWindow::update() {
	sf::Event event;
	while (m_game_window.pollEvent(event)) {
		m_is_done = event.type == sf::Event::Closed;
		if(m_is_done) return;
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) toggle_fullscreen();
	}
}

void GameWindow::toggle_fullscreen() {
	m_is_fullscreen = !m_is_fullscreen;
	destroy();
	create();
}

void GameWindow::begin_draw() { m_game_window.clear(sf::Color::Black); }
void GameWindow::draw(sf::Drawable& drawable) { m_game_window.draw(drawable); }
void GameWindow::end_draw() { m_game_window.display(); }