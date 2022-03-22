#ifndef TREE_TILE_HEADER
#define TREE_TILE_HEADER

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class TreeTile : public ITile {
public:
	TreeTile() { m_tileTexture = Textures::tree; }

	bool isWalkable() const override { return false; }
};

#endif // !TREE_TILE_HEADER


