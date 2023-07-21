#ifndef TEXTURE_ENUM_HEADER_H
#define TEXTURE_ENUM_HEADER_H

#include <magic_enum.hpp>
#include <unordered_map>
#include <optional>

namespace Textures {
enum class ID {
	DEFAULT_PLACEHOLDER_TEXTURE,

	NORRIS_NAKED_DEF_UP_1,
	NORRIS_NAKED_DEF_DOWN_1,
	NORRIS_NAKED_DEF_RIGHT_1,

	NORRIS_RUN_DOWN,
	NORRIS_RUN_UP,
	NORRIS_RUN_RIGHT,

	MAIN_CHARACTER_DEFAULT_SKIN_JUMP,

	MAIN_CHARACTER_ATTACK_RIGHT_SKIN,

	ZOMBIE_IDLE_LEFT,
	ZOMBIE_ATTACK_LEFT,

	GRASS_LANDS_1,

	CROSS_HAIR_DEFAULT,
};

struct TextureMetadata {
	unsigned int number_of_frames;
	std::optional<unsigned int> default_repeats;
	int default_speed;
	std::optional<unsigned int> action_on_frame = std::nullopt;
};

static std::string toString(const ID& textureID) { return magic_enum::enum_name(textureID).data(); }

const static std::unordered_map<ID, std::string> texture_id_to_file_map{
    {ID::DEFAULT_PLACEHOLDER_TEXTURE, "resources/default_texture.png"},

    {ID::NORRIS_NAKED_DEF_UP_1, "resources/character/up.png"},
    {ID::NORRIS_NAKED_DEF_DOWN_1, "resources/character/down.png"},
    {ID::NORRIS_NAKED_DEF_RIGHT_1, "resources/character/right.png"},

    {ID::NORRIS_RUN_DOWN, "resources/character/walk_down.png"},
    {ID::NORRIS_RUN_UP, "resources/character/run_up.png"},
    {ID::NORRIS_RUN_RIGHT, "resources/character/run_right.png"},

    {ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP, "resources/character/jump.png"},

    {ID::MAIN_CHARACTER_ATTACK_RIGHT_SKIN, "resources/character/attack_right.png"},

    {ID::ZOMBIE_IDLE_LEFT, "resources/character/zombie_left_idle.png"},
    {ID::ZOMBIE_ATTACK_LEFT, "resources/character/zombie_left_attack.png"},

    {ID::GRASS_LANDS_1, "resources/tile/grass.png"},

    {ID::CROSS_HAIR_DEFAULT, "resources/ui/crosshair.png"},
};

const static std::unordered_map<ID, TextureMetadata> texture_id_to_texture_metadata{
	{ID::DEFAULT_PLACEHOLDER_TEXTURE, {1, std::nullopt, 0}},

    {ID::NORRIS_NAKED_DEF_UP_1, {1, std::nullopt, 10}},
    {ID::NORRIS_NAKED_DEF_DOWN_1, {4, std::nullopt, 10}},
    {ID::NORRIS_NAKED_DEF_RIGHT_1, {1, std::nullopt, 10}},

    {ID::NORRIS_RUN_DOWN, {4, std::nullopt, 10}},
    {ID::NORRIS_RUN_UP, {4, std::nullopt, 10}},
    {ID::NORRIS_RUN_RIGHT, {4, std::nullopt, 10}},

    {ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP, {9, 1, 5}},

    {ID::MAIN_CHARACTER_ATTACK_RIGHT_SKIN, {3, 1, 15, 2}},

    {ID::ZOMBIE_IDLE_LEFT, {1, std::nullopt, 10}},
    {ID::ZOMBIE_ATTACK_LEFT, {4, 1, 10}}};
}  // namespace Textures

#endif