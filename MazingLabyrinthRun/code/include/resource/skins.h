#ifndef SKINS_HEADER_H
#define SKINS_HEADER_H

#include "../attribute/action_type.h"
#include "../attribute/facingSide.h"
#include "textureEnum.h"

#include <unordered_map>
enum class Skin { MAIN_CHARACTER_START_SKIN, ZOMBIE_DEFAULT_SKIN };

// clang-format off
const static std::unordered_map<Skin, std::unordered_map<ActionType, std::unordered_map<FacingSide, Textures::ID>>>
    skin_animation_side_map = {
        {Skin::MAIN_CHARACTER_START_SKIN, {
				{ActionType::idle, {
							{FacingSide::right, Textures::ID::NORRIS_NAKED_DEF_RIGHT_1},
							{FacingSide::left, Textures::ID::NORRIS_NAKED_DEF_LEFT_1},
							{FacingSide::up, Textures::ID::NORRIS_NAKED_DEF_UP_1},
							{FacingSide::down, Textures::ID::NORRIS_NAKED_DEF_DOWN_1}}},
				{ActionType::run, {
							{FacingSide::right, Textures::ID::NORRIS_RUN_RIGHT},
                            {FacingSide::left, Textures::ID::NORRIS_RUN_LEFT},
                            {FacingSide::up, Textures::ID::NORRIS_RUN_UP},
                            {FacingSide::down, Textures::ID::NORRIS_RUN_DOWN}}},
				{ActionType::jump, {
                            {FacingSide::right, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP},
							{FacingSide::left, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP},
                            {FacingSide::up, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP},
                            {FacingSide::down, Textures::ID::MAIN_CHARACTER_DEFAULT_SKIN_JUMP}}}}
		},
		{Skin::ZOMBIE_DEFAULT_SKIN, {
		 		{ActionType::idle, {
		 				{FacingSide::right, Textures::ID::ZOMBIE_IDLE_LEFT},
		 				{FacingSide::left, Textures::ID::ZOMBIE_IDLE_LEFT},
		 				{FacingSide::up, Textures::ID::ZOMBIE_IDLE_LEFT},
		 				{FacingSide::down, Textures::ID::ZOMBIE_IDLE_LEFT}}},

				{ActionType::attack, {
						{FacingSide::right, Textures::ID::ZOMBIE_ATTACK_LEFT},
		 				{FacingSide::left, Textures::ID::ZOMBIE_ATTACK_LEFT},
		 				{FacingSide::up, Textures::ID::ZOMBIE_ATTACK_LEFT},
		 				{FacingSide::down, Textures::ID::ZOMBIE_ATTACK_LEFT}}}}
		}
};
// clang-format on

const static Textures::ID get_id_of_rotating_texture(Skin skin, ActionType animation, FacingSide side) {
	return skin_animation_side_map.at(skin).at(animation).at(side);
}
const static std::unordered_map<Skin, Textures::ID> skin_texture_id_map;
const static Textures::ID get_id_of_non_rotating_texture(Skin skin) { return skin_texture_id_map.at(skin); }

#endif
