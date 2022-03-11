#include "../include/tile/path.h"

PathTile::PathTile()
	: ITile() {
	setFillColor(tile_color);
}

bool PathTile::isWalkable() const { return true; }

