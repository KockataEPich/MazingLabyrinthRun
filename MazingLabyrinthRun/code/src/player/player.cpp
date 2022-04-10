#include "../include/player/player.h"

#include "../include/player/playerTextureEnum.h"
#include "../include/resource/animation.h"

Animation dRightAnimation("Default Right Animation", defaultRightAnimation, Repeat{-1}, AnimationSpeed{0.3f});
Animation dLeftAnimation("Default Left Animation", defaultLeftAnimation, Repeat{-1}, AnimationSpeed{0.3f});
Animation dUpAnimation("Default Up Animation", defaultUpAnimation, Repeat{-1}, AnimationSpeed{0.3f});
Animation dDownAnimation("Default Down Animation", defaultDownAnimation, Repeat{-1}, AnimationSpeed{0.3f});

#include <SFML/Window/Keyboard.hpp>
Player::Player()
    : m_animate{AnimationPlayer(
          AnimationPlayer::DefaultAnimations{dRightAnimation, dLeftAnimation, dUpAnimation, dDownAnimation})} {
	initialize_player();
}

void Player::initialize_player() {
	m_speed = 100.0f;

	m_sprite.setTexture(m_animate.getCurrentTexture());
	m_sprite.setPosition(sf::Vector2f(100.0f, 100.0f));
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x * m_sprite.getScale().x / 2.0f,
	                                m_sprite.getTexture()->getSize().y * m_sprite.getScale().y / 2.0f));
	m_sprite.setScale(sf::Vector2f(7, 7));
	m_facingSide = FacingSide::down;
}

void Player::move(const float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) moveLeft(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown(deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveUp(deltaTime);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_animate.playDefaultAnimation(m_facingSide);
	else {
		m_animate.update(m_facingSide, deltaTime);
	}
	m_sprite.setTexture(m_animate.getCurrentTexture());
}

void Player::moveRight(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x + (m_speed * deltaTime), m_sprite.getPosition().y);
	m_facingSide = FacingSide::right;
	m_animate.playAnimation(
	    Animation("Run Right Animation", runRightAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
}
void Player::moveLeft(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x - (m_speed * deltaTime), m_sprite.getPosition().y);
	m_facingSide = FacingSide::left;
	m_animate.playAnimation(
	    Animation("Run Left Animation", runLeftAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
}
void Player::moveUp(const float deltaTime) {
	m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - (m_speed * deltaTime));
	m_facingSide = FacingSide::up;
	m_animate.playAnimation(
	    Animation("Run Up Animation", runUpAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
}
void Player::moveDown(const float deltaTime) {
	m_facingSide = FacingSide::down;
	m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + (m_speed * deltaTime));
	m_animate.playAnimation(
	    Animation("Run Down Animation", runDownAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
}
