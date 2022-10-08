#ifndef PLAYER_ACTION_HEADER_H
#define PLAYER_ACTION_HEADER_H
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

enum class ActionList {
	idle,
	move_left,
	move_right,
	move_up,
	move_down,
	jump,
};

const static std::unordered_map<sf::Keyboard::Key, ActionList> key_to_action_map{
	{sf::Keyboard::Key::D, ActionList::move_right},
	{sf::Keyboard::Key::A, ActionList::move_left},
	{sf::Keyboard::Key::S, ActionList::move_down},
	{sf::Keyboard::Key::W, ActionList::move_up},
	{sf::Keyboard::Key::Space, ActionList::jump},
};

inline std::vector<ActionList> determine_player_actions() {
	std::vector<ActionList> action_vector;
	bool player_idle = true;

	for (const auto& action : key_to_action_map)
		if (sf::Keyboard::isKeyPressed(action.first)) {
			action_vector.push_back(action.second);
			player_idle = false;
		}

	if (player_idle) action_vector.push_back(ActionList::idle);

	return action_vector;
};
#endif