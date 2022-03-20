#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

class TreeTile : public sf::Drawable, public sf::Transformable {
public:
	TreeTile(const sf::Vector2f& position) {
		m_texture.loadFromFile(
			"C:/Personal/MazingLabyrinthRun/MazingLabyrinthRun/build/Debug/tree_tile.png");

		this->setPosition(position);
	}

private:
	sf::Texture m_texture;
};