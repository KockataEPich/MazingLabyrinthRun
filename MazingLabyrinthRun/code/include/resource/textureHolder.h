#ifndef TEXTURE_HOLDER_HEADER_H
#define TEXTURE_HOLDER_HEADER_H

#include <SFML/Graphics/Texture.hpp>

#include <map>
#include <stdexcept>
#include <vector>

template <typename T>
class TextureHolder {
public:
	TextureHolder(std::vector<T> allTextures);
	sf::Texture& getTexture(const T&);

private:
	std::map<T, sf::Texture> m_textures;
	void load_textures(std::vector<T> allTextures);
};

template <class T>
TextureHolder<T>::TextureHolder(std::vector<T> allTextures) {
	load_textures(allTextures);
}

template <typename T>
sf::Texture& TextureHolder<T>::getTexture(const T& texture) {
	return m_textures[texture];
}

template <typename T>
void TextureHolder<T>::load_textures(std::vector<T> allTextures) {
	for(auto& texture : allTextures) {
		sf::Texture textureLoad;
		if(!textureLoad.loadFromFile(getFileOfTexture(texture)))
			throw std::runtime_error("A file couldn't be loaded");

		m_textures[texture] = textureLoad;
	}
}

#endif