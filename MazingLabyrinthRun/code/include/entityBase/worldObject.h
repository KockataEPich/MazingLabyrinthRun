#ifndef WORLD_OBJECT_HEADER_H
#define WORLD_OBJECT_HEADER_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
/*
    Super class representing all world objects
    All world objects encapsulate a sprite which they manipulate in some way
    This sprite, with all of its modifications, is drawn
*/
class WorldObject {
public:
	WorldObject() : m_sprite{std::make_unique<sf::Sprite>()} {}
	sf::Sprite& getSprite() { return *m_sprite; }
    sf::Vector2f getPosition() { return m_sprite->getPosition(); }

protected:
	std::unique_ptr<sf::Sprite> m_sprite;
};
#endif