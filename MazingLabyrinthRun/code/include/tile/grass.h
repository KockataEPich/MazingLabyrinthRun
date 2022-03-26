#ifndef GRASS_TILE_HEADER
#define GRASS_TILE_HEADER

#include "iTile.h"

class GrassTile : public ITile {
public:
	GrassTile() { m_tileTexture = Textures::grass; }

	bool isWalkable() const override { return true; }
};

#endif // !GRASS_TILE_HEADER


