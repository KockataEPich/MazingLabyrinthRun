#ifndef PLAYER_HEADER_H
#define PLAYER_HEADER_H

#include "../world/iMovingObject.h"

#include <SFML/Graphics/Texture.hpp>

class Player : public IMovingObject {
public:
	Player();

	sf::Vector2f getPosition() { return m_sprite.getPosition(); }

	void move(const float deltaTime);

private:
	sf::Texture m_playerTexture;

	float m_playerMovementSpeed = 100.0f;
	void initialize_player();

	void moveRight(const float deltaTime);
	void moveLeft(const float deltaTime);
	void moveUp(const float deltaTime);
	void moveDown(const float deltaTime);
};

#endif