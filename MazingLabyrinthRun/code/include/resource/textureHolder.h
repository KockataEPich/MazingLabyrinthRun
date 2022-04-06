#ifndef TEXTURE_HOLDER_HEADER_H
#define TEXTURE_HOLDER_HEADER_H

#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>
#include <stdexcept>
#include <vector>

template <typename T>
void load_textures(std::unordered_map<T, sf::Texture>& textures, std::vector<T> allTextures) {
	for(auto& texture : allTextures) {
		sf::Texture textureLoad;
		if(!textureLoad.loadFromFile(getFileOfTexture(texture)))
			throw std::runtime_error("A file couldn't be loaded");

		textures[texture] = textureLoad;
	}
}

#endif