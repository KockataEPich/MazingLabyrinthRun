#include "../include/resource/resource_manager.h"

ResourceManager* ResourceManager::getInstance() {
	if (!m_textureFactoryInstance) m_textureFactoryInstance = std::unique_ptr<ResourceManager>(new ResourceManager());
	return m_textureFactoryInstance.get();
}

sf::Texture* ResourceManager::getTexture(const Textures::ID& textureId) {
	if (m_textures.find(textureId) == m_textures.end()) insertTexture(textureId);
	return m_textures.at(textureId).get();
}

void ResourceManager::insertTexture(const Textures::ID& textureId) {
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

	std::string textureFile = Textures::texture_id_to_file_map.at(textureId);
	if (!texture->loadFromFile(textureFile))
		throw std::runtime_error("Texture: " + Textures::toString(textureId) + " with file " + textureFile +
		                         " could not be loaded");

	m_textures.insert(std::make_pair(textureId, std::move(texture)));
}