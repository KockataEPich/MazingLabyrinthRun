#include "../include/tile/wall.h"

WallTile::WallTile()
	: ITile() {
	setFillColor(tile_color);
}

bool WallTile::isWalkable() const { return false; }
