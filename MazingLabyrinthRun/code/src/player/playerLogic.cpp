#include "../include/player/playerLogic.h"
#include "../include/player/action.h"
#include "../include/player/execute_actions.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

PlayerLogic::PlayerLogic(){}

PlayerState* PlayerLogic::doLogic(const float deltaTime) {
	m_state.delta_time = deltaTime;
	move(deltaTime);
	return &m_state;
}

void PlayerLogic::initialize() {
	m_state.speed = 100.0f;
	m_sprite->setPosition(sf::Vector2f(0.0f, 0.0f));
	m_sprite->setOrigin(sf::Vector2f(m_sprite->getTexture()->getSize().x * m_sprite->getScale().x / 2.0f,
	                                 m_sprite->getTexture()->getSize().y * m_sprite->getScale().y / 2.0f));
	m_sprite->setScale(sf::Vector2f(6, 6));
	m_state.side = FacingSide::down;
}

void PlayerLogic::move(const float deltaTime) {
	auto list_of_action_names = determine_player_actions();
	auto all_actions = get_action_list(m_sprite, &m_state, list_of_action_names);
	for (auto& action : all_actions) { action->apply(); }
}