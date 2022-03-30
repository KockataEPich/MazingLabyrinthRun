#ifndef PLAYER_HEADER_H
#define PLAYER_HEADER_H

#include "../world/iMovingObject.h"

#include <SFML/Graphics/Texture.hpp>

class Player : public IMovingObject {
public:
	Player();

	sf::Vector2f getPosition() { return m_sprite.getPosition(); }

	void move();

private:
	sf::Texture m_playerTexture;

	float m_playerMovementSpeed = 0.5f;
	void initialize_player();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};

#endif