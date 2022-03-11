#ifndef PATH_TILE_HEADER
#define PATH_TILE_HEADER

#include "iTile.h"

class PathTile : public ITile {
public:
	PathTile();
	bool isWalkable() const override;

private:
	sf::Color tile_color = sf::Color::Magenta;
};

#endif