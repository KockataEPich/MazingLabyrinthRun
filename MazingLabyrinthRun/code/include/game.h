#include "../include/tile.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

class Game {
public:
	Game();

	std::vector<sf::Drawable*> drawable_components() {
		return m_drawable_components;
	}

	std::vector<std::vector<Tile>> display_matrix() {
		return m_display_matrix;
	}

	void update();

private:
	sf::RectangleShape m_square;
	std::vector<sf::Drawable*> m_drawable_components;
	std::vector<std::vector<Tile>> m_display_matrix;
};