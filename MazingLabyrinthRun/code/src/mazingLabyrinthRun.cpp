#include "../include/mazingLabyrinthRun.h"
#include "../include/tile/tileEnum.h"
#include "../include/tile/tree.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

MazingLabyrinthRun::MazingLabyrinthRun()
	: m_window("MazingLabyrinthRun", sf::Vector2u(1280, 720)) {
	initialize_game();
};

void MazingLabyrinthRun::initialize_game() {
	//populate the world with grass
	int tiles_x = m_window.getWindowSize().x / 32;
	int tiles_y = m_window.getWindowSize().y / 32;

	for(int i = 0; i < m_window.getWindowSize().x; i = i + 32)
		for(int j = 0; j < m_window.getWindowSize().y; j = j + 32)
			m_worldObjectHolder.add_to_world_objects(
				*m_tileFactory.create(TileType::grass, sf::Vector2f(i, j)));
}

void MazingLabyrinthRun::handleInput() { }

void MazingLabyrinthRun::update() { m_window.update(); }

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