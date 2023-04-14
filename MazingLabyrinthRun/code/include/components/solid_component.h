#ifndef SOLID_COMPONENT_HEADER
#define SOLID_COMPONENT_HEADER

#include <SFML/Graphics/Rect.hpp>
struct SolidComponent : public Component<SolidComponent> {
	SolidComponent() = default;
	SolidComponent(sf::FloatRect hitbox) : m_hitbox{hitbox} {};
	sf::FloatRect m_hitbox;
};

#endif