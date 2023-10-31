// ################## THIS FILE IS GENERATED ##################
#ifndef BOUNDARY_COMPONENT_HEADER
#define BOUNDARY_COMPONENT_HEADER

#include <component_base/component.h>
#include <SFML/Graphics/Rect.hpp>

struct BoundaryComponent : public Component<BoundaryComponent> {
	BoundaryComponent() = default;
	explicit BoundaryComponent(
		sf::FloatRect&& hitbox) : 
		hitbox{hitbox}{}

	sf::FloatRect hitbox;
};
#endif