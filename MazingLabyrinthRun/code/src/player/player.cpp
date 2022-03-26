#include "../include/player/player.h"

Player::Player() { initialize_player(); }

void Player::initialize_player() {
	if(!m_playerTexture.loadFromFile("resources/character/knight.png"))
		throw "Player texture couldn't be loaded";

	m_sprite.setTexture(m_playerTexture);
	m_sprite.setPosition(sf::Vector2f(100.0f, 100.0f));
	m_sprite.setScale(sf::Vector2f(5, 5));
}
