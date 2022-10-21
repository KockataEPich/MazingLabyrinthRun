#ifndef SPRITE_COMPONENT_HEADER
#define SPRITE_COMPONENT_HEADER

#include "../component_base/component.h"

#include <sfml/Graphics/Sprite.hpp>

class SpriteComponent : public Component<SpriteComponent> {
public:
	SpriteComponent(sf::Sprite&& sprite) : m_sprite{sprite} {};
	SpriteComponent() = default;
	sf::Sprite& sprite() {
		int x = 2;
		return m_sprite;
	};

private:
	sf::Sprite m_sprite;
};

#endif