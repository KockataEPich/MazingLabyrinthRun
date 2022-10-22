#include "../include/system/systems/render_system.h"
#include "../include/resource/resource_manager.h"
void Render::render() {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<SpriteComponent> sprite;
		m_parent_world->unpack(entity, sprite);

		auto& real_sprite = sprite->m_sprite;
		m_render_window.draw(real_sprite);
	}
}