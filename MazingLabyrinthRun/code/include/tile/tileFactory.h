#ifndef TILE_FACTORY_HEADER
#define TILE_FACTORY_HEADER

#include "path.h"
#include "iTile.h"
#include "wall.h"
#include "tileEnum.h"

#include <memory>

class TileFactory {
public:
	std::unique_ptr<ITile> create(const TileType& type);
	std::unique_ptr<ITile> create(const TileType& type, const std::pair<int, int>& coordinates);
};

#endif //TILE_FACTORY_HEADER