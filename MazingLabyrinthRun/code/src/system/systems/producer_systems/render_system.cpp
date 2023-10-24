#include <generated/systems/producer_systems/render_system.h>
#include <generated/components/data_components/boundary_component.h>

namespace {
void remove_entity_if_it_exists(std::vector<std::pair<sf::Sprite*, Entity>>& entities_and_sprites, Entity entity) {
	auto entity_inside = std::find_if(entities_and_sprites.begin(),
	                                  entities_and_sprites.end(),
	                                  [entity](std::pair<sf::Sprite*, Entity>& pair) { return entity == pair.second; });
	std::swap(*entity_inside, entities_and_sprites.back());
	entities_and_sprites.pop_back();
}
}  // namespace

void RenderSystem::for_every_entity(
	Entity entity,
	SpriteComponent& sprite,
	ElevationLevelComponent& elevation_level){

	std::sort(m_level_two_sprites.begin(), m_level_two_sprites.end(), [](const auto& lhs, const auto& rhs) {
		return lhs.first->getPosition().y < rhs.first->getPosition().y;
	});

	draw_level(m_level_one_sprites);
	draw_level(m_level_two_sprites, false);
	draw_level(m_level_UI_sprites, true);
}


void RenderSystem::register_entity(Entity const& entity) {
	ComponentHandle<SpriteComponent> sprite;
	ComponentHandle<ElevationLevelComponent> elevation;

	m_parent_world->unpack(entity, sprite, elevation);
	get_level_vector(elevation.level).push_back({&sprite.sprite, entity});
}

void RenderSystem::unregister_entity(Entity const& entity) {
	ComponentHandle<ElevationLevelComponent> elevation;
	m_parent_world->unpack(entity, elevation);
	remove_entity_if_it_exists(get_level_vector(elevation.level), entity);
}

void RenderSystem::draw_level(std::vector<std::pair<sf::Sprite*, Entity>>& sprites_and_entities, bool draw_hitbox) {
	for (auto& sprite_and_entity : sprites_and_entities) {
		m_render_window.draw(*sprite_and_entity.first);
		if (!draw_hitbox) continue;

		for (const auto& entity : m_parent_world->get_all_entities_who_have_component<BoundaryComponent>()) {
			ComponentHandle<BoundaryComponent> boundary;
			m_parent_world->unpack(entity, boundary);

			auto box = boundary.hitbox;
			sf::RectangleShape rectangle({box.width, box.height});
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineThickness(5);
			rectangle.setOutlineColor(sf::Color::Magenta);
			rectangle.setPosition({boundary.hitbox.left, boundary.hitbox.top});
			m_render_window.draw(rectangle);
		}
	}
}

std::vector<std::pair<sf::Sprite*, Entity>>& RenderSystem::get_level_vector(ElevationLevel level) {
	if (level == ElevationLevel::one) return m_level_one_sprites;
	if (level == ElevationLevel::two) return m_level_two_sprites;
	return m_level_UI_sprites;
}

