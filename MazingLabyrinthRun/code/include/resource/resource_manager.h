#ifndef RESOURCE_MANAGER_HEADER_H
#define RESOURCE_MANAGER_HEADER_H

#include "texture_enum.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <unordered_map>

class ResourceManager {
public:
	ResourceManager(ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;

	static ResourceManager* get_instance();

	sf::Texture* get_texture(const Textures::ID&);
	sf::Font* get_font(const std::string);

protected:
	ResourceManager() {}
	inline static std::unique_ptr<ResourceManager> m_texture_factory_instance;

private:
	std::unordered_map<Textures::ID, std::unique_ptr<sf::Texture>> m_textures;
	std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
	void insert_texture(const Textures::ID&);
	void insert_font(const std::string);
};

#endif