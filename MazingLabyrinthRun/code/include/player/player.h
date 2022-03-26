#ifndef PLAYER_HEADER_H
#define PLAYER_HEADER_H

#include "../world/iWorldObject.h"

#include <SFML/Graphics/Texture.hpp>

class Player : public IWorldObject {
public:
	Player();

private:
	sf::Texture m_playerTexture;
	void initialize_player();
};

#endif