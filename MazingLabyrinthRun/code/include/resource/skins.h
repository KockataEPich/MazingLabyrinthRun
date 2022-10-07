#ifndef SKINS_HEADER_H
#define SKINS_HEADER_H

#include "../attribute/facingSide.h"
#include "textureEnum.h"

#include <unordered_map>
enum class Skin { MAIN_CHARACTER_START_SKIN };
enum class AnimationType { MAIN_CHARACTER_DEFAULT_STATIONARY, MAIN_CHARACTER_DEFAULT_RUN, MAIN_CHARACTER_DEFAULT_JUMP };

// clang-format off
const static std::unordered_map<Skin, std::unordered_map<AnimationType, std::unordered_map<FacingSide, Textures::ID>>>
    skin_animation_side_map = {
        {Skin::MAIN_CHARACTER_START_SKIN, {
					{AnimationType::MAIN_CHARACTER_DEFAULT_STATIONARY,{
							{FacingSide::right, Textures::ID::NORRIS_NAKED_DEF_RIGHT_1},
							{FacingSide::left, Textures::ID::NORRIS_NAKED_DEF_LEFT_1},
							{FacingSide::up, Textures::ID::NORRIS_NAKED_DEF_UP_1},
							{FacingSide::down, Textures::ID::NORRIS_NAKED_DEF_DOWN_1}}},

                 	{AnimationType::MAIN_CHARACTER_DEFAULT_RUN,{
							{FacingSide::right, Textures::ID::NORRIS_RUN_RIGHT},
                            {FacingSide::left, Textures::ID::NORRIS_RUN_LEFT},
                            {FacingSide::up, Textures::ID::NORRIS_RUN_UP},
                            {FacingSide::down, Textures::ID::NORRIS_RUN_DOWN}}},

					{AnimationType::MAIN_CHARACTER_DEFAULT_JUMP,{
                            	{FacingSide::right, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP},
                            	{FacingSide::left, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP},
                            	{FacingSide::up, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP},
                            	{FacingSide::down, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP}}}}}};
// clang-format on

const static Textures::ID get_id_of_rotating_texture(Skin skin, AnimationType animation, FacingSide side) {
	return skin_animation_side_map.at(skin).at(animation).at(side);
}
const static std::unordered_map<Skin, Textures::ID> skin_texture_id_map;
const static Textures::ID get_id_of_non_rotating_texture(Skin skin) { return skin_texture_id_map.at(skin); }

#endif
