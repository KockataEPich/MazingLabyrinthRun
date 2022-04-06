#ifndef PLAYER_TEXTURE_HOLDER_HEADER_H
#define PLAYER_TEXTURE_HOLDER_HEADER_H

#include <SFML/Graphics/Texture.hpp>

#include "playerTextureEnum.h"
#include <unordered_map>

class PlayerTextureHolder {
public:
	PlayerTextureHolder();
	sf::Texture& getTexture(const PlayerTextures&);

private:
	std::unordered_map<PlayerTextures, sf::Texture> m_textures;
	void load_textures();
};
#endif