#ifndef BOUNDARY_COMPONENT_HEADER
#define BOUNDARY_COMPONENT_HEADER

#include <component_base/component.h>
#include <components/data_components/transform_component.h>
#include <SFML/Graphics/Rect.hpp>

struct BoundaryComponent : public Component<BoundaryComponent> {
	BoundaryComponent() = default;
	BoundaryComponent(sf::FloatRect hitbox) : m_hitbox{hitbox} {};
	sf::FloatRect m_hitbox;
};

#endif