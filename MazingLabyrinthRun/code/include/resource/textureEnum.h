#ifndef TEXTURE_ENUM_HEADER_H
#define TEXTURE_ENUM_HEADER_H

#include <magic_enum.hpp>
#include <stdexcept>
#include <unordered_map>
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

	MAIN_CHARACTER_DEFAULT_SKIN_JUMP,

	ZOMBIE_IDLE_LEFT,
	ZOMBIE_ATTACK_LEFT,
};

struct TextureMetadata {
	int number_of_frames;
	int default_repeats;
	float default_speed;
};

static std::string toString(const ID& textureID) { return magic_enum::enum_name(textureID).data(); }

const static std::unordered_map<ID, std::string> texture_id_to_file_map{
    {ID::NORRIS_NAKED_DEF_UP_1, "resources/character/up.png"},
    {ID::NORRIS_NAKED_DEF_DOWN_1, "resources/character/down.png"},
    {ID::NORRIS_NAKED_DEF_LEFT_1, "resources/character/left.png"},
    {ID::NORRIS_NAKED_DEF_RIGHT_1, "resources/character/right.png"},

    {ID::NORRIS_RUN_DOWN, "resources/character/walk_down.png"},
    {ID::NORRIS_RUN_UP, "resources/character/run_up.png"},
    {ID::NORRIS_RUN_LEFT, "resources/character/run_left.png"},
    {ID::NORRIS_RUN_RIGHT, "resources/character/run_right.png"},

    {ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP, "resources/character/jump.png"},

    {ID::ZOMBIE_IDLE_LEFT, "resources/character/zombie_left_idle.png"},
    {ID::ZOMBIE_ATTACK_LEFT, "resources/character/zombie_left_attack.png"},
};

const static std::unordered_map<ID, TextureMetadata> texture_id_to_texture_metadata{
    {ID::NORRIS_NAKED_DEF_UP_1, {1, -1, 0.2f}},
    {ID::NORRIS_NAKED_DEF_DOWN_1, {4, -1, 0.2f}},
    {ID::NORRIS_NAKED_DEF_LEFT_1, {1, -1, 0.2f}},
    {ID::NORRIS_NAKED_DEF_RIGHT_1, {1, -1, 0.2f}},

    {ID::NORRIS_RUN_DOWN, {4, -1, 0.2f}},
    {ID::NORRIS_RUN_UP, {4, -1, 0.2f}},
    {ID::NORRIS_RUN_LEFT, {4, -1, 0.2f}},
    {ID::NORRIS_RUN_RIGHT, {4, -1, 0.2f}},

    {ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP, {9, 1, 0.1f}},

    {ID::ZOMBIE_IDLE_LEFT, {1, -1, 0.1f}},
    {ID::ZOMBIE_ATTACK_LEFT, {4, 1, 0.2f}}
};
}  // namespace Textures

#endif