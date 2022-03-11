#include "../include/tile/tileFactory.h"

std::unique_ptr<ITile> TileFactory::create(const TileType& type) {
	switch(type) {
	case TileType::path:
		return std::make_unique<PathTile>();
	case TileType::wall:
		return std::make_unique<WallTile>();
	}
}
std::unique_ptr<ITile> TileFactory::create(const TileType& type,
										   const std::pair<int, int>& coordinates) {
	switch(type) {
	case TileType::path: {
		auto path_tile = std::make_unique<PathTile>();
		path_tile.get()->setPosition(static_cast<float>(coordinates.first * 36),
									 static_cast<float>(coordinates.second * 36));
		return path_tile;
	}
	case TileType::wall: {
		auto wall_tile = std::make_unique<WallTile>();
		wall_tile.get()->setPosition(static_cast<float>(coordinates.first * 36),
									 static_cast<float>(coordinates.second * 36));
		return wall_tile;
	}
	}
}