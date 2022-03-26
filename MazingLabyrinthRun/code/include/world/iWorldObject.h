#ifndef WORLD_OBJECT_HEADER_H
#define WORLD_OBJECT_HEADER_H

#include <SFML/Graphics/Sprite.hpp>
/*
	Interface representing all world objects
	All world objects encapsulate a sprite which they manipulate in some way
	This sprite, with all of its modifications, is drawn
*/
class IWorldObject {
public:
	sf::Sprite& getSprite() { return m_sprite; }

protected:
	sf::Sprite m_sprite;
};

#endif