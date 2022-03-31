#include "../include/tile/tileFactory.h"

#include "../include/tile/tree.h"
#include "../include/tile/rock.h"
#include "../include/tile/grass.h"

//template <typename T>
//std::unique_ptr<ITile> makeUniqueTile(TextureManager& textureManager) {
//	auto tile = std::make_unique<T>();
//	tile.get()->getSprite().setTexture(textureManager.getTexture(tile.get()->getTextureOfTile()));
//
//	return tile;
//}
//
//template <typename T>
//std::unique_ptr<ITile> makeUniqueTileWithPosition(TextureManager& textureManager,
//												  const sf::Vector2f& coordinates) {
//	auto tile = std::make_unique<T>();
//	tile.get()->getSprite().setTexture(textureManager.getTexture(tile.get()->getTextureOfTile()));
//	tile.get()->getSprite().setPosition(coordinates);
//
//	return tile;
//}
//
//
//std::unique_ptr<ITile> TileFactory::create(const TileType& type) {
//	switch(type) {
//	case TileType::tree: 
//		return makeUniqueTile<TreeTile>(m_textureManager);
//	case TileType::rock: 
//		return makeUniqueTile<RockTile>(m_textureManager);
//	case TileType::grass:
//		return makeUniqueTile<GrassTile>(m_textureManager);
//	default:
//		std::abort();
//	}
//}
//std::unique_ptr<ITile> TileFactory::create(const TileType& type, const sf::Vector2f& coordinates) {
//	switch(type) {
//	case TileType::tree: 
//		return makeUniqueTileWithPosition<TreeTile>(m_textureManager, coordinates);
//	case TileType::rock:
//		return makeUniqueTileWithPosition<RockTile>(m_textureManager, coordinates);
//	case TileType::grass:
//		return makeUniqueTileWithPosition<GrassTile>(m_textureManager, coordinates);
//	default:
//		std::abort();
//	}
//}



