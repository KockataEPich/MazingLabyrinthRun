#include <utils/move_functions/linear_move_function.h>

#include <numbers>  // for std::numbers::pi
#include <cmath>

sf::Vector2f calculate_linear_velocity(const sf::Vector2f& origin, 
									   const sf::Vector2f& final_point, 
									   const float speed) {
	sf::Vector2f triangle_sides = {std::abs(origin.x - final_point.x),
	                               std::abs(origin.y - final_point.y)};

	float angle = std::atan2(triangle_sides.y, triangle_sides.x) * 180 / std::numbers::pi;
	float angle_end_point = std::numbers::pi * 2 * angle / 360;

	float x_offset = speed * std::cos(angle_end_point);
	float y_offset = speed * std::sin(angle_end_point);

	sf::Vector2f result_vec;
	return {(origin.x < final_point.x) ? x_offset : x_offset * -1,
	        (origin.y < final_point.y) ? y_offset : y_offset * -1};
}

