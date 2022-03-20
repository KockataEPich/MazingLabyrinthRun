#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class TreeTile : public sf::Sprite{
public:
	TreeTile(const sf::Vector2f& position) {
		m_texture.loadFromFile(
			"tree.png");

		this->setTexture(m_texture);
		this->setPosition(position);
	}

private:
	sf::Texture m_texture;
};