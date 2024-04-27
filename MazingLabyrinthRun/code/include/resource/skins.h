#ifndef SKINS_HEADER_H
#define SKINS_HEADER_H

#include <SFML/Graphics/Rect.hpp>

#include "../attribute/action_type.h"
#include "../attribute/facing_side.h"

#include "texture_enum.h"
#include <unordered_map>
enum class Skin { 
	DEFAULT_PLACEHOLDER_SKIN, 
	MAIN_CHARACTER_START_SKIN, 
	ZOMBIE_DEFAULT_SKIN, 
	CROSSHAIR_DEFAULT_SKIN, 
	EMPTY_ABILITY_BLOCK,
	ABILITY_BLOCK,
	FIREBALL_1,
	GRASS_LANDS_1,
};

// clang-format off
const static std::unordered_map<Skin, std::unordered_map<ActionType, Textures::ID>>
    skin_animation_side_map = {
        {Skin::MAIN_CHARACTER_START_SKIN, {
				{ActionType::idle, Textures::ID::MC_DEF},
				{ActionType::move, Textures::ID::MC_DEF_RUN},
				{ActionType::attack, Textures::ID::MC_DEF_CAST}}
		},
		{Skin::ZOMBIE_DEFAULT_SKIN, {
				{ActionType::idle, Textures::ID::ZOMBIE_DEFAULT},
				{ActionType::move, Textures::ID::ZOMBIE_DEFAULT},
				{ActionType::attack, Textures::ID::ZOMBIE_DEFAULT}}
		},
};
// clang-format on

const static Textures::ID get_id_of_rotating_texture(Skin skin, ActionType animation) {
	return skin_animation_side_map.at(skin).at(animation);
}
const static Textures::ID get_idle_animation(Skin skin) {
	return skin_animation_side_map.at(skin).at(ActionType::idle);
}

const static std::unordered_map<Skin, sf::FloatRect> get_boundary_side_offsets_of_skin = {
    {Skin::MAIN_CHARACTER_START_SKIN, {0.73f, 0.63f, 0.73f, 0.88f}},
    {Skin::ZOMBIE_DEFAULT_SKIN, {0.8, 0.65, 0.8, 0.95}},
    {Skin::CROSSHAIR_DEFAULT_SKIN, {0.9, 0.9, 0.9, 0.9}},
    {Skin::FIREBALL_1, {0.9, 0.7, 1.0, 0.8}},
    {Skin::GRASS_LANDS_1, {0.8, 0.8, 0.8, 0.8}},
};
#endif
