#include "../include/system/systems/render_system.h"

void Render::register_entity(Entity const& entity) {
	ComponentHandle<SpriteComponent> sprite;
	ComponentHandle<ElevationLevelComponent> elevation;

	m_parent_world->unpack(entity, sprite, elevation);

	if (elevation->m_level == ElevationLevel::one)
		level_one_sprites.push_back({&sprite->m_sprite, entity});
	else
		level_two_sprites.push_back({&sprite->m_sprite, entity});
}

void Render::unregister_entity(Entity const& entity) {
	ComponentHandle<ElevationLevelComponent> elevation;
	m_parent_world->unpack(entity, elevation);

	if (elevation->m_level == ElevationLevel::one) {
		auto entity_inside =
		    std::find_if(level_one_sprites.begin(),
		                 level_one_sprites.end(),
		                 [entity](std::pair<sf::Sprite*, Entity>& pair) { return entity == pair.second; });
		std::swap(*entity_inside, level_one_sprites.back());
		level_one_sprites.pop_back();
	} else {
		auto entity_inside =
		    std::find_if(level_two_sprites.begin(),
		                 level_two_sprites.end(),
		                 [entity](std::pair<sf::Sprite*, Entity>& pair) { return entity == pair.second; });
		std::swap(*entity_inside, level_two_sprites.back());
		level_two_sprites.pop_back();
	}
}

void Render::draw_level(std::vector<std::pair<sf::Sprite*, Entity>>& sprites) {
	for (auto& [sprite, entity] : sprites) m_render_window.draw(*sprite);
}

void Render::render() {
	// Hot path. This operation will probably be one of the most common ones and thus removing the
	// abstraction of entity handlers and using the sprites directly will be beneficial for performance
	std::sort(level_two_sprites.begin(), level_two_sprites.end(), [](const auto& lhs, const auto& rhs) {
		return lhs.first->getPosition().y < rhs.first->getPosition().y;
	});

	draw_level(level_one_sprites);
	draw_level(level_two_sprites);
}