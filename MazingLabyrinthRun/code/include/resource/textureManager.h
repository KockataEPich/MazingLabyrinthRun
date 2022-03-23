#ifndef TEXTURE_MANAGER_HEADER
#define TEXTURE_MANAGER_HEADER

#include "textureEnum.h"

#include <SFML/Graphics/Texture.hpp>

class TextureManager {
public:
	TextureManager();
	sf::Texture& getTexture(const Textures& texture);

private:
	sf::Texture m_treeTexture;
	sf::Texture m_rockTexture;

	void loadTextures();
	std::string getFileOfTexture(const Textures& texture);
};

#endif