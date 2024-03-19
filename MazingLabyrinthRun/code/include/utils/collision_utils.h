#ifndef COLLISION_UTILS_HEADER
#define COLLISION_UTILS_HEADER

#include <SFML/System/Vector2.hpp>
struct CollisionInfo {
	sf::Vector2f contact_point = {0, 0};
	sf::Vector2f contact_normal = {0, 0};
	float contact_time;
};
#endif