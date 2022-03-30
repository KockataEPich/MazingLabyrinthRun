#include "../include/player/player.h"

#include <SFML/Window/Keyboard.hpp>
Player::Player() { initialize_player(); }

void Player::initialize_player() {
	m_speed = 100.0f;

	if(!m_playerTexture.loadFromFile("resources/character/knight.png"))
		throw "Player texture couldn't be loaded";

	m_sprite.setTexture(m_playerTexture);
	m_sprite.setPosition(sf::Vector2f(100.0f, 100.0f));
	m_sprite.setOrigin(
		sf::Vector2f(m_sprite.getTexture()->getSize().x * m_sprite.getScale().x / 2.0f,
					 m_sprite.getTexture()->getSize().y * m_sprite.getScale().y / 2.0f));
	m_sprite.setScale(sf::Vector2f(3, 3));
}

void Player::move(const float deltaTime) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		moveRight(deltaTime);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		moveLeft(deltaTime);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		moveDown(deltaTime);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		moveUp(deltaTime);
}

void Player::moveRight(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x + (m_speed * deltaTime),
						 m_sprite.getPosition().y);
}
void Player::moveLeft(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x - (m_speed * deltaTime),
						 m_sprite.getPosition().y);
}
void Player::moveUp(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x,
						 m_sprite.getPosition().y - (m_speed * deltaTime));
}
void Player::moveDown(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x,
						 m_sprite.getPosition().y + (m_speed * deltaTime));
}
