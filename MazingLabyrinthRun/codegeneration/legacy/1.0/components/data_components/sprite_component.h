// ################## THIS FILE IS GENERATED ##################
#ifndef SPRITE_COMPONENT_HEADER
#define SPRITE_COMPONENT_HEADER

#include <component_base/component.h>
#include <sfml/Graphics/Sprite.hpp>

struct SpriteComponent : public Component<SpriteComponent> {
	SpriteComponent() = default;
	explicit SpriteComponent(
		sf::Sprite&& sprite) : 
		m_sprite{std::move(sprite)}{};

	sf::Sprite m_sprite;
};
#endif