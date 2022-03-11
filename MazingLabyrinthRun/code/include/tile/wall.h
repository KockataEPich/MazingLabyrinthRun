#ifndef WALL_TILE_HEADER
#define WALL_TILE_HEADER

#include "iTile.h"

class WallTile : public ITile {
public:
	WallTile();
	bool isWalkable() const override;

private:
	sf::Color tile_color = sf::Color::Black;
};

#endif