#include "../include/player/playerTextureHolder.h"
#include <stdexcept>
PlayerTextureHolder::PlayerTextureHolder() { load_textures(); }
sf::Texture& PlayerTextureHolder::getTexture(const PlayerTextures& texture) {
	return m_textures[texture];
}

void PlayerTextureHolder::load_textures() {
	//for(auto& texture : all_textures_player) {
	//	sf::Texture textureLoad;
	//	if(!textureLoad.loadFromFile(getFileOfTexture(texture)))
	//		throw std::runtime_error("A file couldn't be loaded");

	//	m_textures[texture] = textureLoad;
	//}
}