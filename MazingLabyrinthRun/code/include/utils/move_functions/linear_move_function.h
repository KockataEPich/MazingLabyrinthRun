#ifndef LINEAR_MOVE_FUNCTION_HEADER
#define LINEAR_MOVE_FUNCTION_HEADER

#include <SFML/System/Vector2.hpp>
#include <functional>
sf::Vector2f calculate_linear_velocity(const sf::Vector2f& origin, const sf::Vector2f& final_point, const float speed);
#endif