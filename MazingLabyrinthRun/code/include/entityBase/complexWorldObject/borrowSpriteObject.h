#ifndef BORROW_SPRITE_OBJECT_HEADER_H
#	define BORROW_SPRITE_OBJECT_HEADER_H

#include <SFML/Graphics/Sprite.hpp>

class BorrowSpriteObject {
public:
	void setSprite(sf::Sprite* sprite) { m_sprite = sprite; }

protected:
	sf::Sprite* m_sprite;
};

#endif