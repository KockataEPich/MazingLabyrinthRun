#include "../include/resource/resource_manager.h"
#include <stdexcept>

ResourceManager* ResourceManager::get_instance() {
	if (!m_texture_factory_instance)
		m_texture_factory_instance = std::unique_ptr<ResourceManager>(new ResourceManager());
	return m_texture_factory_instance.get();
}

sf::Texture* ResourceManager::get_texture(const Textures::ID& texture_id) {
	if (m_textures.find(texture_id) == m_textures.end()) insert_texture(texture_id);
	return m_textures.at(texture_id).get();
}

void ResourceManager::insert_texture(const Textures::ID& texture_id) {
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

	std::string texture_file = Textures::texture_id_to_file_map.at(texture_id);
	if (!texture->loadFromFile(texture_file))
		throw std::runtime_error("Texture: " + Textures::toString(texture_id) + " with file " + texture_file +
		                         " could not be loaded");

	m_textures.insert(std::make_pair(texture_id, std::move(texture)));
}

sf::Font* ResourceManager::get_font(const std::string font_name) {
	if (!m_fonts.contains(font_name)) insert_font(font_name);
	return m_fonts.at(font_name).get();
}

void ResourceManager::insert_font(const std::string font_name) {
	auto font = std::make_unique<sf::Font>();
	if (!font->loadFromFile(font_name))
		throw std::runtime_error("Font name: " + font_name + " could not be loaded");

	m_fonts.insert(std::make_pair(font_name, std::move(font)));
}