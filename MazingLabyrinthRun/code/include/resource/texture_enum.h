#ifndef TEXTURE_ENUM_HEADER_H
#define TEXTURE_ENUM_HEADER_H

#include <magic_enum.hpp>
#include <unordered_map>
#include <optional>

namespace Textures {
enum class ID {
	DEFAULT_PLACEHOLDER_TEXTURE,

	MC_DEF,
    MC_DEF_RUN,
    MC_DEF_CAST,

	GRASS_LANDS_1,

	CROSS_HAIR_DEFAULT,
    EMPTY_ABILITY_BLOCK,
    ABILITY_BLOCK,

    ZOMBIE_DEFAULT,
    ZOMBIE_FLASHED,

    FIREBALL_1,
};

struct TextureMetadata {
	unsigned int number_of_frames;
	int default_speed;
	std::optional<unsigned int> default_repeats = std::nullopt;
	std::optional<unsigned int> action_on_frame = std::nullopt;
};

static std::string toString(const ID& textureID) { return magic_enum::enum_name(textureID).data(); }

const static std::unordered_map<ID, std::string> texture_id_to_file_map{
    {ID::DEFAULT_PLACEHOLDER_TEXTURE, "resources/default_texture.png"},

    {ID::MC_DEF, "resources/character/MC/MC_IDLE.png"},
    {ID::MC_DEF_RUN, "resources/character/MC/MC_RUN.png"},
    {ID::MC_DEF_CAST, "resources/character/MC/MC_CASTING.png"},

    {ID::GRASS_LANDS_1, "resources/tile/grass.png"},

    {ID::CROSS_HAIR_DEFAULT, "resources/ui/crosshair.png"},
    {ID::EMPTY_ABILITY_BLOCK, "resources/ui/empty_ability_block.png"},
    {ID::ABILITY_BLOCK, "resources/ui/ability_block.png"},

    {ID::ZOMBIE_DEFAULT, "resources/character/zombie_left_idle.png"},
    {ID::ZOMBIE_FLASHED, "resources/character/plain_white_zombie.png"},
    

    {ID::FIREBALL_1, "resources/character/MC/FIREBALL_RED.png"}
};

const static std::unordered_map<ID, TextureMetadata> texture_id_to_texture_metadata{
    {ID::DEFAULT_PLACEHOLDER_TEXTURE, {1, 0}},
    {ID::MC_DEF, {1, 10}},
    {ID::MC_DEF_RUN, {4, 10}},
    {ID::MC_DEF_CAST, {3,10}},
    {ID::ZOMBIE_DEFAULT, {1, 10}},
    {ID::ZOMBIE_FLASHED, {1, 10}}
};
}  // namespace Textures

#endif