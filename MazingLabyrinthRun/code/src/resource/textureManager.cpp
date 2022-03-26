#include "../include/resource/textureManager.h"
#include <stdexcept>

TextureManager::TextureManager() { loadTextures(); }

sf::Texture& TextureManager::getTexture(const Textures& texture) {
	switch(texture) {
	case Textures::tree:
		return m_treeTexture;
	case Textures::rock:
		return m_rockTexture;
	case Textures::grass:
		return m_grassTexture;
	default:
		throw std::runtime_error("A member function for texture is not defined");
	}
}

std::string TextureManager::getFileOfTexture(const Textures& texture) {
	switch(texture) {
	case Textures::tree:
		return "resources/tile/tree.png";
	case Textures::rock:
		return "resources/tile/rock.png";
	case Textures::grass:
		return "resources/tile/grass.png";
	default:
		throw std::runtime_error("A file is not defined for texture");
	}
}

void TextureManager::loadTextures() {
	for(auto& texture : all_textures) {
		if(!getTexture(texture).loadFromFile(getFileOfTexture(texture)))
			throw "Error loading file " + getFileOfTexture(texture);
	}
}