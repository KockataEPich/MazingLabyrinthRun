#include "../include/system/systems/render_system.h"

void Render::render() {

	std::sort(std::begin(m_registered_entities),
	          std::end(m_registered_entities),
	          [this](const auto& lhs, const auto& rhs) {
		          ComponentHandle<SpriteComponent> lhs_sprite;
		          ComponentHandle<SpriteComponent> rhs_sprite;

		          m_parent_world->unpack(lhs, lhs_sprite);
		          m_parent_world->unpack(rhs, rhs_sprite);

		          auto lhs_pos = lhs_sprite->m_sprite.getPosition().y;
		          auto rhs_pos = rhs_sprite->m_sprite.getPosition().y;

		          return  lhs_pos < rhs_pos;
	          });

	for (auto& entity : m_registered_entities) {
		ComponentHandle<SpriteComponent> sprite;
		m_parent_world->unpack(entity, sprite);

		auto& real_sprite = sprite->m_sprite;
		m_render_window.draw(real_sprite);
	}
}