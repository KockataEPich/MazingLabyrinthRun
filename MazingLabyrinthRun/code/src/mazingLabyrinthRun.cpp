#include "../include/mazingLabyrinthRun.h"
#include "../include/tile/tree.h"
#include "../include/tile/tileEnum.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

MazingLabyrinthRun::MazingLabyrinthRun()
	: m_window("MazingLabyrinthRun", sf::Vector2u(1280, 720)){
};

void MazingLabyrinthRun::handleInput() { }

void MazingLabyrinthRun::update() {
	m_window.update();
	// action
}

void MazingLabyrinthRun::render() {
	auto tree_tile = m_tileFactory.create(TileType::tree, sf::Vector2f(100.0f, 100.0f));
	auto rock_tile = m_tileFactory.create(TileType::rock, sf::Vector2f(150.0f, 150.0f));
	auto rock2_tile = m_tileFactory.create(TileType::rock, sf::Vector2f(299.0f, 200.0f));
	auto tree2_tile = m_tileFactory.create(TileType::tree, sf::Vector2f(299.0f, 200.0f));

	m_window.beginDraw();
	m_window.draw(tree_tile.get()->getSprite());
	m_window.draw(rock_tile.get()->getSprite());
	m_window.draw(rock2_tile.get()->getSprite());
	m_window.draw(tree2_tile.get()->getSprite());
	m_window.endDraw();
}

void MazingLabyrinthRun::start_game() {
	while(!m_window.isDone()) {
		update();
		render();
	}
}