#include <system/systems/producer_systems/render_system.h>
#include <components/data_components/solid_component.h>
namespace {
void remove_entity_if_it_exists(std::vector<std::pair<sf::Sprite*, Entity>>& entities_and_sprites, Entity entity) {
	auto entity_inside = std::find_if(entities_and_sprites.begin(),
	                                  entities_and_sprites.end(),
	                                  [entity](std::pair<sf::Sprite*, Entity>& pair) { return entity == pair.second; });
	std::swap(*entity_inside, entities_and_sprites.back());
	entities_and_sprites.pop_back();
}

}  // namespace
void Render::register_entity(Entity const& entity) {
	ComponentHandle<SpriteComponent> sprite;
	ComponentHandle<ElevationLevelComponent> elevation;

	m_parent_world->unpack(entity, sprite, elevation);
	get_level_vector(elevation->m_level).push_back({&sprite->m_sprite, entity});
}

void Render::unregister_entity(Entity const& entity) {
	ComponentHandle<ElevationLevelComponent> elevation;
	m_parent_world->unpack(entity, elevation);
	remove_entity_if_it_exists(get_level_vector(elevation->m_level), entity);
}

void Render::update() {
	// Hot path. This operation will probably be one of the most common ones and thus removing the
	// abstraction of entity handlers and using the sprites directly will be beneficial for performance
	std::sort(level_two_sprites.begin(), level_two_sprites.end(), [](const auto& lhs, const auto& rhs) {
		return lhs.first->getPosition().y < rhs.first->getPosition().y;
	});

	draw_level(level_one_sprites);
	draw_level(level_two_sprites, true);
}

void Render::draw_level(std::vector<std::pair<sf::Sprite*, Entity>>& sprites_and_entities, bool draw_hitbox) {
	for (auto& sprite_and_entity : sprites_and_entities) { 
		m_render_window.draw(*sprite_and_entity.first); 
		if (!draw_hitbox) continue;

		for (const auto& entity : m_parent_world->get_all_entities_who_have_component<SolidComponent>()) {
			ComponentHandle<SolidComponent> solid;
			m_parent_world->unpack(entity, solid);

			auto box = solid->m_hitbox;
			sf::RectangleShape rectangle({box.width, box.height});
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineThickness(5);
			rectangle.setOutlineColor(sf::Color::Magenta);
			rectangle.setPosition({solid->m_hitbox.left, solid->m_hitbox.top});
			m_render_window.draw(rectangle);
		}
	}
}
std::vector<std::pair<sf::Sprite*, Entity>>& Render::get_level_vector(ElevationLevel level) {
	if (level == ElevationLevel::one) return level_one_sprites;
	return level_two_sprites;
}