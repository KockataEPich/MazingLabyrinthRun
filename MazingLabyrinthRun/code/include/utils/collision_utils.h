#ifndef COLLISION_UTILS_HEADER
#define COLLISION_UTILS_HEADER

#include <SFML/System/Vector2.hpp>
struct CollisionInfo {
	sf::Vector2f contact_point;
	sf::Vector2f contact_normal;
	float contact_time;
};
#endif