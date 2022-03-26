#ifndef SPRITE_HOLDER_HEADER_H
#define SPRITE_HOLDER_HEADER_H

#include "../world/iWorldObject.h"

#include <memory>
#include <vector>

class SpriteHolder {
public:
	SpriteHolder();

	std::vector<sf::Sprite>& getAllWorldObjects() { return m_allWorldObjects; }
	void add_to_world_objects(const sf::Sprite& sprite) { m_allWorldObjects.push_back(sprite); }

private :
	std::vector<sf::Sprite> m_allWorldObjects;
};

#endif