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

    FIREBALL_1
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

    {ID::MC_DEF, "resources/character/MC/MC_IDLE.png"},
    {ID::MC_DEF_RUN, "resources/character/MC/MC_RUN.png"},
    {ID::MC_DEF_CAST, "resources/character/MC/MC_CASTING.png"},

    {ID::GRASS_LANDS_1, "resources/tile/grass.png"},

    {ID::CROSS_HAIR_DEFAULT, "resources/ui/crosshair.png"},

    {ID::FIREBALL_1, "resources/character/MC/FIREBALL_RED.png"}
};

const static std::unordered_map<ID, TextureMetadata> texture_id_to_texture_metadata{
	{ID::DEFAULT_PLACEHOLDER_TEXTURE, {1, std::nullopt, 0}},

    {ID::MC_DEF, {1, std::nullopt, 10}},
    {ID::MC_DEF_RUN, {4, std::nullopt, 10}},
    {ID::MC_DEF_CAST, {3, std::nullopt, 10}}};
}  // namespace Textures

#endif