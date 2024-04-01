#ifndef SFML_RECT_HELPERS
#define SFML_RECT_HELPERS

#include <SFML/Graphics/Rect.hpp>
#include <utils/sfml_vector_helpers.h>

inline sf::FloatRect get_expanded_rectangle(const sf::FloatRect& rectangle, const sf::Vector2f total_expansion) {
	return {rectangle.left - total_expansion.x * 0.5f,
	        rectangle.top - total_expansion.y * 0.5f,
	        rectangle.width + total_expansion.x,
	        rectangle.height + total_expansion.y};
}

inline sf::FloatRect get_expanded_rectangle(const sf::FloatRect& rectangle, const float total_expansion_coeficient) {
	return {rectangle.left * total_expansion_coeficient * 0.5f,
	        rectangle.top * total_expansion_coeficient * 0.5f,
	        rectangle.width * total_expansion_coeficient,
	        rectangle.height * total_expansion_coeficient};
}


#endif