#ifndef TEXTURE_ENUM_HEADER_H
#define TEXTURE_ENUM_HEADER_H

#include <magic_enum.hpp>
#include <stdexcept>

namespace Textures {
enum class ID {
	NORRIS_NAKED_DEF_UP_1,
	NORRIS_NAKED_DEF_DOWN_1,
	NORRIS_NAKED_DEF_LEFT_1,
	NORRIS_NAKED_DEF_RIGHT_1,

	NORRIS_RUN_DOWN,
	NORRIS_RUN_UP,
	NORRIS_RUN_LEFT,
	NORRIS_RUN_RIGHT,
};

static std::string toString(const ID& textureID) { return magic_enum::enum_name(textureID).data(); }

static std::string getFileOfTexture(const ID& textureID) {
	switch (textureID) {
		case ID::NORRIS_NAKED_DEF_UP_1: return "resources/character/up.png";
		case ID::NORRIS_NAKED_DEF_DOWN_1: return "resources/character/down.png";
		case ID::NORRIS_NAKED_DEF_LEFT_1: return "resources/character/left.png";
		case ID::NORRIS_NAKED_DEF_RIGHT_1: return "resources/character/right.png";

		case ID::NORRIS_RUN_DOWN: return "resources/character/walk_down.png";
		case ID::NORRIS_RUN_UP: return "resources/character/run_up.png";
		case ID::NORRIS_RUN_LEFT: return "resources/character/run_left.png";
		case ID::NORRIS_RUN_RIGHT: return "resources/character/run_right.png";
	}

	throw std::runtime_error("Texture: " + toString(textureID) + " has no resource file associated with it");
}

static int getNumberOfFrames(const ID& textureID) {
	switch (textureID) {
		case ID::NORRIS_NAKED_DEF_UP_1: return 1;
		case ID::NORRIS_NAKED_DEF_DOWN_1: return 4;
		case ID::NORRIS_NAKED_DEF_LEFT_1: return 1;
		case ID::NORRIS_NAKED_DEF_RIGHT_1: return 1;

		case ID::NORRIS_RUN_DOWN: return 4;
		case ID::NORRIS_RUN_UP: return 4;
		case ID::NORRIS_RUN_LEFT: return 4;
		case ID::NORRIS_RUN_RIGHT: return 4;
	}

	throw std::runtime_error("Texture: " + toString(textureID) + " has no number of frames specified");
}

}  // namespace Textures

#endif