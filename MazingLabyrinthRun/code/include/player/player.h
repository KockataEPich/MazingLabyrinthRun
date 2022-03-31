#ifndef PLAYER_HEADER_H
#define PLAYER_HEADER_H

#include "../world/iMovingObject.h"
#include "../player/playerTextureEnum.h"
#include "../resource/textureHolder.h"

#include <SFML/Graphics/Texture.hpp>

class Player : public IMovingObject {
public:
	Player(TextureHolder<PlayerTextures>& textureHolder);

	sf::Vector2f getPosition() { return m_sprite.getPosition(); }

	void move(const float deltaTime) override;

private:
	TextureHolder<PlayerTextures>& m_textureHolder;
	void initialize_player();

	void moveRight(const float deltaTime);
	void moveLeft(const float deltaTime);
	void moveUp(const float deltaTime);
	void moveDown(const float deltaTime);
};

#endif