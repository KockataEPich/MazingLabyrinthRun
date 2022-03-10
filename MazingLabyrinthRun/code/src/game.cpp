#include "../include/game.h"

Game::Game()
	: m_square{sf::Vector2f(50.0f, 50.0f)} {

	for(int i = 0; i <= 1280; i += 36) {
		std::vector<Tile> temp_vector;
		for(int j = 0; j <= 720; j += 36) {
			Tile tile;
			tile.setPosition(sf::Vector2f(i, j));
			temp_vector.push_back(tile);
		}

		m_display_matrix.push_back(temp_vector);
	}
	m_square.setFillColor(sf::Color::White);
}

void Game::update() { }
