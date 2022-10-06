#ifndef TEXTURE_ENUM_HEADER_H
#define TEXTURE_ENUM_HEADER_H

#include <magic_enum.hpp>
#include <stdexcept>

namespace Textures {
enum class ID {
	NORRIS_NAKED_WALK_UP_1,
	NORRIS_NAKED_WALK_UP_2,
	NORRIS_NAKED_WALK_UP_3,
	NORRIS_NAKED_WALK_DOWN_1,
	NORRIS_NAKED_WALK_DOWN_2,
	NORRIS_NAKED_WALK_DOWN_3,
	NORRIS_NAKED_WALK_LEFT_1,
	NORRIS_NAKED_WALK_LEFT_2,
	NORRIS_NAKED_WALK_LEFT_3,
	NORRIS_NAKED_WALK_RIGHT_1,
	NORRIS_NAKED_WALK_RIGHT_2,
	NORRIS_NAKED_WALK_RIGHT_3,
	TILE_TREE,
	TILE_ROCK,
	TILE_GRASS,
	KNIGHT_CP1,
	KNIGHT_CP2,
	SWORD_DEFAULT,
	SWORD_FANCY,
	GOLDEN_CROWN,
	SILVER_CROWN
};

static std::string toString(const ID& textureID) { return magic_enum::enum_name(textureID).data(); }

static std::string getFileOfTexture(const ID& textureID) {
	switch (textureID) {
		case ID::NORRIS_NAKED_WALK_UP_1: return "resources/character/up.png";
		case ID::NORRIS_NAKED_WALK_UP_2: return "resources/character/up2.png";
		case ID::NORRIS_NAKED_WALK_UP_3: return "resources/character/up3.png";
		case ID::NORRIS_NAKED_WALK_DOWN_1: return "resources/character/down.png";
		case ID::NORRIS_NAKED_WALK_DOWN_2: return "resources/character/down2.png";
		case ID::NORRIS_NAKED_WALK_DOWN_3: return "resources/character/down3.png";
		case ID::NORRIS_NAKED_WALK_LEFT_1: return "resources/character/left.png";
		case ID::NORRIS_NAKED_WALK_LEFT_2: return "resources/character/left2.png";
		case ID::NORRIS_NAKED_WALK_LEFT_3: return "resources/character/left3.png";
		case ID::NORRIS_NAKED_WALK_RIGHT_1: return "resources/character/right.png";
		case ID::NORRIS_NAKED_WALK_RIGHT_2: return "resources/character/rightRunBetween.png";
		case ID::NORRIS_NAKED_WALK_RIGHT_3: return "resources/character/rightRunEnd.png";
		case ID::TILE_TREE: return "resources/character/up.png";
		case ID::TILE_ROCK: return "resources/tile/grass.png";
		case ID::TILE_GRASS: return "resources/tile/grass.png";
		case ID::KNIGHT_CP1: return "resources/character/knightCP1.png";
		case ID::KNIGHT_CP2: return "resources/character/knightCP2.png";
		case ID::SWORD_DEFAULT: return "resources/tile/sword_default.png";
		case ID::SWORD_FANCY: return "resources/tile/sword_fancy.png";
		case ID::GOLDEN_CROWN: return "resources/tile/golden_crown.png";
		case ID::SILVER_CROWN: return "resources/tile/grey_crown.png";
	}

	throw std::runtime_error("Texture: " + toString(textureID) + " has no resource file associated with it");
}

}  // namespace Textures

#endif