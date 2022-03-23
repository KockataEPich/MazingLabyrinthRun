#ifndef I_TILE_HEADER
#define I_TILE_HEADER

#include "../resource/textureEnum.h"
#include "../world/iWorldObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>

const sf::Vector2f tileSize{1.0f, 1.0f};

class ITile : public IWorldObject {
public:
	ITile() { m_sprite.setScale(tileSize); };

	virtual bool isWalkable() const = 0;

	Textures getTextureOfTile() { return m_tileTexture; };

protected:
	Textures m_tileTexture;
	sf::Sprite m_sprite;
};

#endif