#ifndef RESOURCE_MANAGER_HEADER_H
#define RESOURCE_MANAGER_HEADER_H

#include "texture_enum.h"

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <unordered_map>

class ResourceManager {
public:
	ResourceManager(ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;

	static ResourceManager* getInstance();

	sf::Texture* getTexture(const Textures::ID&);

protected:
	ResourceManager() {}
	inline static std::unique_ptr<ResourceManager> m_textureFactoryInstance;

private:
	std::unordered_map<Textures::ID, std::unique_ptr<sf::Texture>> m_textures;
	void insertTexture(const Textures::ID&);
};

#endif