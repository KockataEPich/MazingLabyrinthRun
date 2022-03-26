#ifndef PLAYER_HEADER_H
#define PLAYER_HEADER_H

#include "../world/iWorldObject.h"

#include <SFML/Graphics/Texture.hpp>

class Player : public IWorldObject {
public:
	Player();

	sf::Vector2f getPosition() { return m_sprite.getPosition(); }

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

private:
	sf::Texture m_playerTexture;
	void initialize_player();
};

#endif