#include "../include/player/player.h"
#include "../include/player/playerTextureEnum.h"
#include <SFML/Window/Keyboard.hpp>
Player::Player(Animation<PlayerTextures>& animator)
	: m_animate{animator} {
	initialize_player();
}

void Player::initialize_player() {
	m_speed = 100.0f;

	m_sprite.setTexture(m_animate.getCurrentTexture());
	m_sprite.setPosition(sf::Vector2f(100.0f, 100.0f));
	m_sprite.setOrigin(
		sf::Vector2f(m_sprite.getTexture()->getSize().x * m_sprite.getScale().x / 2.0f,
					 m_sprite.getTexture()->getSize().y * m_sprite.getScale().y / 2.0f));
	m_sprite.setScale(sf::Vector2f(7, 7));
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

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
	   !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_animate.playDefaultAnimation();
	else {
		m_animate.update(deltaTime);
	}
	m_sprite.setTexture(m_animate.getCurrentTexture());
}

void Player::moveRight(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x + (m_speed * deltaTime),
						 m_sprite.getPosition().y);
	m_animate.playAnimation(0.2f, runRightAnimation);
}
void Player::moveLeft(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x - (m_speed * deltaTime),
						 m_sprite.getPosition().y);
	m_animate.playAnimation(0.2f, runLeftAnimation);
}
void Player::moveUp(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x,
						 m_sprite.getPosition().y - (m_speed * deltaTime));
	m_animate.playAnimation(0.2f, runUpAnimation);
}
void Player::moveDown(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x,
						 m_sprite.getPosition().y + (m_speed * deltaTime));
	m_animate.playAnimation(0.2f, runDownAnimation);
}
