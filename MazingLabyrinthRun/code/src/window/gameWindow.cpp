#include "../include/window/gameWindow.h"

#include <SFML/Window/Event.hpp>

GameWindow::GameWindow() { setup("MazingLabyrinthRun", sf::Vector2u(1280, 720)); }
GameWindow::GameWindow(const std::string& title, const sf::Vector2u& size) { setup(title, size); }

GameWindow::~GameWindow() { destroy(); }

void GameWindow::setup(const std::string& title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	create();
}

void GameWindow::create() {
	auto style = m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_gameWindow.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
}

void GameWindow::destroy() { m_gameWindow.close(); }

bool GameWindow::isDone() { return m_isDone; }
bool GameWindow::isFullscreen() { return m_isFullscreen; }
sf::Vector2u GameWindow::getWindowSize() { return m_windowSize; }

void GameWindow::update() {
	sf::Event event;
	while(m_gameWindow.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			m_isDone = true;
		} else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
			toggleFullscreen();
		}
	}
}

void GameWindow::toggleFullscreen() {
	m_isFullscreen = !m_isFullscreen;
	destroy();
	create();
}

void GameWindow::beginDraw() { m_gameWindow.clear(sf::Color::Black); }
void GameWindow::draw(sf::Drawable& drawable) { m_gameWindow.draw(drawable); }
void GameWindow::draw(IWorldObject& worldObject) { m_gameWindow.draw(worldObject.getSprite()); }
void GameWindow::draw(WorldObjectHolder& worldObjectHolder) {
	for(auto& worldObject : worldObjectHolder.getAllWorldObjects())
		draw(*worldObject);
}
void GameWindow::endDraw() { m_gameWindow.display(); }