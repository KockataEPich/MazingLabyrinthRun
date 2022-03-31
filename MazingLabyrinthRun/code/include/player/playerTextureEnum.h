#ifndef PLAYER_TEXTURE_ENUM_H
#define PLAYER_TEXTURE_ENUM_H

enum class PlayerTextures { up, down, left, right };

#include <array>
#include <stdexcept>
static std::array<PlayerTextures, 4> all_textures_player{
	PlayerTextures::up, PlayerTextures::down, PlayerTextures::left, PlayerTextures::right};

static std::string getFileOfTexture(const PlayerTextures& texture) {
	switch(texture) {
	case PlayerTextures::up:
		return "resources/character/up.png";
	case PlayerTextures::down:
		return "resources/character/down.png";
	case PlayerTextures::left:
		return "resources/character/left.png";
	case PlayerTextures::right:
		return "resources/character/right.png";
	default:
		throw std::runtime_error("A file is not defined for texture");
	}
}
#endif