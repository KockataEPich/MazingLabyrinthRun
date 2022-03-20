#ifndef I_TILE_HEADER
#define I_TILE_HEADER

#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
const sf::Vector2f tileSize{36.0f, 36.0f};

class ITile : public sf::RectangleShape {
public:
	ITile() { setSize(tileSize); };
	virtual bool isWalkable() const = 0;

private:
};

#endif