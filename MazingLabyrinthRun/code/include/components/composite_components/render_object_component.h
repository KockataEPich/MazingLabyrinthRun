#ifndef RENDER_OBJECT_COMPONENT_HEADER
#define RENDER_OBJECT_COMPONENT_HEADER

#include <component_base/component.h>

#include <components/data_components/sprite_component.h>
#include <optional>
#include <SFML/Graphics/Text.hpp>

struct RenderObjectComponent : public Component<RenderObjectComponent> {
	RenderObjectComponent() = default;
	RenderObjectComponent(int health) : m_health{health} {}

	SpriteComponent& m_sprite_component;
	std::optional<sf::Text> m_healthpoint_text = std::nullopt;
};
#endif