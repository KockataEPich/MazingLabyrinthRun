#ifndef HIT_BOX_HEADER_H
#define HIT_BOX_HEADER_H

#include "../components/transform_component.h"
#include <SFML/System/Vector2.hpp>

struct HitBox {
	sf::Vector2f top_left;
	sf::Vector2f bottom_right;
};

//get_hitbox_from_coordinates()

#endif