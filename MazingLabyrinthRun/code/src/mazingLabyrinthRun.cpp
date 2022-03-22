#include "../include/mazingLabyrinthRun.h"
#include "../include/game.h"
#include "../include/tile/tileMap.h"
#include "../include/tile/tree.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

MazingLabyrinthRun::MazingLabyrinthRun()
	: m_window("MazingLabyrinthRun", sf::Vector2u(1280, 720)){};

void MazingLabyrinthRun::handleInput() { }

void MazingLabyrinthRun::update() {
	m_window.update();
	// action
}

void MazingLabyrinthRun::render() {
	TreeTile tile(sf::Vector2f(100.0f, 100.0f));
	m_window.beginDraw();
	//m_window.draw(tile);
	m_window.endDraw();
}

void MazingLabyrinthRun::start_game() {
	while(!m_window.isDone()) {
		update();
		render();
	}
}