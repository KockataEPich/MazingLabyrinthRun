#ifndef TILE_FACTORY_HEADER
#define TILE_FACTORY_HEADER

#include "iTile.h"
#include "tileEnum.h"

#include "../resource/textureManager.h"
#include <memory>

class TileFactory {
public:
	TileFactory(const TextureManager& texture_manager)
		: m_textureManager{texture_manager} {};

	std::unique_ptr<ITile> create(const TileType& type);
	std::unique_ptr<ITile> create(const TileType& type, const sf::Vector2f& coordinates);

private:
	TextureManager m_textureManager;
};

#endif //TILE_FACTORY_HEADER