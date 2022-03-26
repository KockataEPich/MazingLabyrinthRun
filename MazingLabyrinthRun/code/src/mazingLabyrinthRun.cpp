#include "../include/mazingLabyrinthRun.h"
#include "../include/tile/tileEnum.h"
#include "../include/tile/tree.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

MazingLabyrinthRun::MazingLabyrinthRun()
	: m_window("MazingLabyrinthRun", sf::Vector2u(1280, 720)) {
	//populate the world with grass
	int tiles_x = m_window.getWindowSize().x / 32;
	int tiles_y = m_window.getWindowSize().y / 32;

	for(int i = 0; i < m_window.getWindowSize().x; i = i + 32)
		for(int j = 0; j < m_window.getWindowSize().y; j = j + 32)
			m_spriteHolder.add_to_world_objects(
				m_tileFactory.create(TileType::grass, sf::Vector2f(i, j)).get()->getSprite());

	// initialise the player

	if(!m_player_texture.loadFromFile("resources/character/knight.png"))
		return;
	m_player.setTexture(m_player_texture);
	m_player.setPosition(sf::Vector2f(100.0f, 100.0f));
	m_player.setScale(sf::Vector2f(5, 5));
};

void MazingLabyrinthRun::handleInput() { }

void MazingLabyrinthRun::update() { m_window.update(); }

void MazingLabyrinthRun::render() {
	m_window.beginDraw();
	for(auto& sprite : m_spriteHolder.getAllWorldObjects())
		m_window.draw(sprite);
	m_window.draw(m_player);
	m_window.endDraw();
}

void MazingLabyrinthRun::start_game() {
	while(!m_window.isDone()) {
		update();
		render();
	}
}