#include "../include/player/player.h"
#include "../include/player/playerTextureEnum.h"
#include <SFML/Window/Keyboard.hpp>
Player::Player(PlayerTextureHolder& textureHolder)
	: m_textureHolder{textureHolder} {
	initialize_player();
}

void Player::initialize_player() {
	m_speed = 100.0f;

	m_sprite.setTexture(m_textureHolder.getTexture(PlayerTextures::right));
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
	m_sprite.setTexture(m_textureHolder.getTexture(PlayerTextures::right));
}
void Player::moveLeft(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x - (m_speed * deltaTime),
						 m_sprite.getPosition().y);
	m_sprite.setTexture(m_textureHolder.getTexture(PlayerTextures::left));
}
void Player::moveUp(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x,
						 m_sprite.getPosition().y - (m_speed * deltaTime));
	m_sprite.setTexture(m_textureHolder.getTexture(PlayerTextures::up));
}
void Player::moveDown(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x,
						 m_sprite.getPosition().y + (m_speed * deltaTime));
	m_sprite.setTexture(m_textureHolder.getTexture(PlayerTextures::down));
}
