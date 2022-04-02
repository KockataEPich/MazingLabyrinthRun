#ifndef PLAYER_TEXTURE_ENUM_H
#define PLAYER_TEXTURE_ENUM_H

enum class PlayerTextures {
	up,
	up2,
	up3,
	down,
	down2,
	down3,
	left,
	left2,
	left3,
	right,
	right2,
	right3
};

#include <stdexcept>
#include <vector>
static std::vector<PlayerTextures> allPlayerTextures{PlayerTextures::up,
													 PlayerTextures::up2,
													 PlayerTextures::up3,
													 PlayerTextures::down,
													 PlayerTextures::down2,
													 PlayerTextures::down3,
													 PlayerTextures::left,
													 PlayerTextures::left2,
													 PlayerTextures::left3,
													 PlayerTextures::right,
													 PlayerTextures::right2,
													 PlayerTextures::right3};

static std::string getFileOfTexture(const PlayerTextures& texture) {
	switch(texture) {
	case PlayerTextures::up:
		return "resources/character/up.png";
	case PlayerTextures::up2:
		return "resources/character/up2.png";
	case PlayerTextures::up3:
		return "resources/character/up3.png";
	case PlayerTextures::down:
		return "resources/character/down.png";
	case PlayerTextures::down2:
		return "resources/character/down2.png";
	case PlayerTextures::down3:
		return "resources/character/down3.png";
	case PlayerTextures::left:
		return "resources/character/left.png";
	case PlayerTextures::left2:
		return "resources/character/left2.png";
	case PlayerTextures::left3:
		return "resources/character/left3.png";
	case PlayerTextures::right:
		return "resources/character/right.png";
	case PlayerTextures::right2:
		return "resources/character/rightRunBetween.png";
	case PlayerTextures::right3:
		return "resources/character/rightRunEnd.png";
	default:
		throw std::runtime_error("A file is not defined for texture");
	}
}

static std::vector<PlayerTextures> runRightAnimation{
	PlayerTextures::right, PlayerTextures::right2, PlayerTextures::right, PlayerTextures::right3};
static std::vector<PlayerTextures> runLeftAnimation{
	PlayerTextures::left, PlayerTextures::left2, PlayerTextures::left, PlayerTextures::left3};
static std::vector<PlayerTextures> runUpAnimation{
	PlayerTextures::up, PlayerTextures::up2, PlayerTextures::up, PlayerTextures::up3};
static std::vector<PlayerTextures> runDownAnimation{
	PlayerTextures::down, PlayerTextures::down2, PlayerTextures::down, PlayerTextures::down3};

#endif