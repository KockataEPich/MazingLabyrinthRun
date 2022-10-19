#ifndef SPRITE_COMPONENT_HEADER
#define SPRITE_COMPONENT_HEADER

#include "../component_base/component.h"
#include <sfml/Graphics/Sprite.hpp>

struct SpriteComponent : Component<SpriteComponent>{
	SpriteComponent(sf::Sprite&& sprite) : m_sprite{sprite}{};
	sf::Sprite m_sprite;
};

#endif