#include "../include/player/playerLogic.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

PlayerLogic::PlayerLogic(){}

PlayerState* PlayerLogic::doLogic(const float deltaTime) {
	move(deltaTime);
	return &m_state;
}

void PlayerLogic::initialize() {
	m_speed = 100.0f;
	
	m_sprite->setPosition(sf::Vector2f(100.0f, 100.0f));
	m_sprite->setOrigin(sf::Vector2f(m_sprite->getTexture()->getSize().x * m_sprite->getScale().x / 2.0f,
	                                 m_sprite->getTexture()->getSize().y * m_sprite->getScale().y / 2.0f));
	m_sprite->setScale(sf::Vector2f(7, 7));
	m_state.side = FacingSide::down;
}

void PlayerLogic::move(const float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) moveLeft(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveUp(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_state.currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_JUMP;
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_state.currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_STATIONARY;
}

void PlayerLogic::moveRight(const float deltaTime) {
	m_sprite->setPosition(m_sprite->getPosition().x + (m_speed * deltaTime), m_sprite->getPosition().y);
	m_state.side = FacingSide::right;
	m_state.currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_RUN;
}
void PlayerLogic::moveLeft(const float deltaTime) {
	m_sprite->setPosition(m_sprite->getPosition().x - (m_speed * deltaTime), m_sprite->getPosition().y);
	m_state.side = FacingSide::left;
	m_state.currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_RUN;
	
}
void PlayerLogic::moveUp(const float deltaTime) {
	m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y - (m_speed * deltaTime));
	m_state.side = FacingSide::up;
	m_state.currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_RUN;
}
void PlayerLogic::moveDown(const float deltaTime) {
	m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + (m_speed * deltaTime));
	m_state.side = FacingSide::down;
	m_state.currentAnimation = AnimationType::MAIN_CHARACTER_DEFAULT_RUN;
}
