#include "../include/mazingLabyrinthRun.h"
#include "../include/tile/tileEnum.h"
#include "../include/tile/tree.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

MazingLabyrinthRun::MazingLabyrinthRun()
	: m_window("MazingLabyrinthRun", sf::Vector2u(1920, 1080)) {
	initialize_game();
};

void MazingLabyrinthRun::initialize_game() {
	m_camera = sf::View(sf::Vector2f(0.0f, 0.0f),
						sf::Vector2f(m_window.getWindowSize().x, m_window.getWindowSize().y));

	m_worldObjectHolder.initializeWorld(m_window.getWindowSize());
}

void MazingLabyrinthRun::handleInput() { m_player.move(); }

void MazingLabyrinthRun::update() {
	m_window.update();
	handleInput();
	m_camera.setCenter(m_player.getPosition());
	m_window.setView(m_camera);
}

void MazingLabyrinthRun::render() {
	m_window.beginDraw();
	m_window.draw(m_worldObjectHolder);
	m_window.draw(m_player);
	m_window.endDraw();
}

void MazingLabyrinthRun::start_game() {
	while(!m_window.isDone()) {
		update();
		render();
	}
}