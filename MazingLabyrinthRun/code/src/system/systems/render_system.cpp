#include "../include/system/systems/render_system.h"
#include "../include/resource/resource_manager.h"
void Render::render() {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<SpriteComponent> sprite;
		m_parent_world->unpack(entity, sprite);

		sf::Texture text;
		text.loadFromFile("resources/tile/grass.png");
		sprite->m_sprite.setTexture(text);
		m_render_window->draw(sprite->m_sprite);
	}
}