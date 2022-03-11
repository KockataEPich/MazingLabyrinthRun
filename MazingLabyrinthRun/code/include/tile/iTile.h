#ifndef I_TILE_HEADER
#define I_TILE_HEADER

#include <SFML/Graphics/RectangleShape.hpp>
#include <string>

class ITile : public sf::RectangleShape {
public:
	ITile() { setSize(size); };
	virtual bool isWalkable() const = 0;

private:
	sf::Vector2f size{36.0f, 36.0f};
};

#endif