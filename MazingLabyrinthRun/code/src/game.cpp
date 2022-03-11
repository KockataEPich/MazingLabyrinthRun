#include "../include/game.h"

Game::Game() { }

void Game::update() { }

void Game::fill_map() {
	const auto wall = TileType::wall;
	const auto path = TileType::path;

	std::vector<std::vector<TileType>> matrix = {{wall, wall, wall, wall, wall, wall},
												 {path, path, path, wall, path, wall},
												 {wall, wall, path, path, path, wall},
												 {wall, wall, wall, path, wall, wall},
												 {wall, path, path, path, path, path},
												 {wall, wall, wall, wall, wall, wall}};

	for(int i = 0; i < matrix.size(); i++)
		for(int j = 0; j < matrix[i].size(); j++) {
			m_tiles.push_back(tileFactory.create(matrix[i][j], std::make_pair(j, i)));
		}
}