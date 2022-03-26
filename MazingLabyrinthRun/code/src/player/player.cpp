#include "../include/player/player.h"

Player::Player() { initialize_player(); }

void Player::initialize_player() {
	if(!m_playerTexture.loadFromFile("resources/character/knight.png"))
		throw "Player texture couldn't be loaded";

	m_sprite.setTexture(m_playerTexture);
	m_sprite.setPosition(sf::Vector2f(100.0f, 100.0f));
	m_sprite.setOrigin(
		sf::Vector2f(m_sprite.getTexture()->getSize().x * m_sprite.getScale().x / 2.0f,
					 m_sprite.getTexture()->getSize().y * m_sprite.getScale().y / 2.0f));
	m_sprite.setScale(sf::Vector2f(3, 3));
}

void Player::moveRight() {
	m_sprite.setPosition(m_sprite.getPosition().x + 0.5f, m_sprite.getPosition().y);
}
void Player::moveLeft() {
	m_sprite.setPosition(m_sprite.getPosition().x - 0.5f, m_sprite.getPosition().y);
}
void Player::moveUp() {
	m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - 0.5f);
}
void Player::moveDown() {
	m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + 0.5f);
}
