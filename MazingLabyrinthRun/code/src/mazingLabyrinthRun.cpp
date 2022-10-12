#include "../include/mazingLabyrinthRun.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

MazingLabyrinthRun::MazingLabyrinthRun() : m_window("MazingLabyrinthRun", sf::Vector2u(1920, 1080)) {
	initialize_game();
	m_player = std::make_unique<Player>(Player());
	m_zombie = std::make_unique<Zombie>(Zombie());

	tile_texture.loadFromFile("resources/tile/grass.png");

	for (int i = -1600; i <= 1600; i += 160) {
		for (int j = 1600; j >= -1600; j -= 160) {
			sf::Sprite tile;
			tile.setPosition(sf::Vector2f((float)i, (float)j));
			tile.setTexture(tile_texture);
			tile.scale(sf::Vector2f(5.0f, 5.0f));
			grass_lands.push_back(tile);
		}
	}
};

void MazingLabyrinthRun::initialize_game() {
	m_camera = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_window.getWindowSize().x, m_window.getWindowSize().y));
}

void MazingLabyrinthRun::handleInput() {}

void MazingLabyrinthRun::update() {
	m_player->play(m_deltaTime);
	m_zombie->play(m_deltaTime);

	m_window.update();
	m_camera.setCenter(m_player->getPosition());
	m_window.setView(m_camera);
}

void MazingLabyrinthRun::render() {
	m_window.beginDraw();
	for (auto& grass : grass_lands) m_window.draw(grass);

	m_window.draw(*m_player);
	m_window.draw(*m_zombie);

	m_window.endDraw();
}

void MazingLabyrinthRun::start_game() {
	while (!m_window.isDone()) {
		m_deltaTime = getElapsed().asSeconds();
		handleInput();
		update();
		render();
		restartClock();
	}
}