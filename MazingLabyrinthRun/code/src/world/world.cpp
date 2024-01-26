#include <world/world.h>
#include <game.h>

#include <generated/components/data_components/transform_component.h>
#include <entity_base/entity_handle.h>
#include <entity_creation/entity_builder/builders/grass_lands_tile_builder.h>
#include <entity_creation/entity_builder/builders/zombie_builder.h>
#include <entity_creation/entity_builder/builders/player_builder.h>

#include <generated/components/data_components/boundary_component.h>
#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/target_for_direction_component.h>
#include <generated/components/data_components/health_points_component.h>

#include <generated/components/basic_components/solid_component.h>
#include <generated/components/basic_components/default_collision_armor_component.h>
#include <generated/components/basic_components/mouse_component.h>

#include <utils/component_utils.h>

bool World::place_entity(const Entity entity, sf::Vector2f position) {
	EntityHandle entity_handle{entity, m_game};
	entity_handle.get_component<TransformComponent>()->position = position;
	return true;
}

void World::init() {
	GrassLandsTileBuilder grass_builder;
	ZombieEntityBuilder zombie_builder;
	auto zombie2 = m_game->create_entity();
	zombie_builder.build_entity(zombie2);
	zombie2.add_components(
		std::make_unique<SolidComponent>(),
		std::make_unique<BoundaryComponent>(
	    get_hitbox_based_on_transform_component(*zombie2.get_component<TransformComponent>())),
		std::make_unique<DefaultCollisionArmorComponent>(),
		std::make_unique<TargetForDirectionComponent>(),
		std::make_unique<HealthPointsComponent>());

	m_game->world->place_entity(zombie2.entity, {32.0f, 32.0f});

	for (int i = -1600; i <= 1600; i += 160) {
		int counter = 0;
		for (int j = 1600; j >= -1600; j -= 160) {
			auto grass_land = m_game->create_entity();
			grass_builder.build_entity(grass_land);

			/*if (counter == 10) {
			    auto zombie = m_world->create_entity();
			    zombie_builder.build_entity(zombie);
			    zombie.add_component(std::make_unique<SolidComponent>());
			    zombie.add_component(std::make_unique<DefaultCollisionArmorComponent>());
			    zombie.add_component(std::make_unique<HealthPointsComponent>());
			    zombie.add_component(std::make_unique<TargetForDirectionComponent>());
			    zombie.add_component(std::make_unique<BoundaryComponent>(
			        get_hitbox_based_on_transform_component(*zombie.get_component<TransformComponent>())));
			    m_world->place_entity(zombie, {(float)i, (float)j});
			    counter = 0;
			}
			counter++;*/
			place_entity(grass_land.entity, {(float)i, (float)j});

			// grass_land.add_component(std::make_unique<BoundaryComponent>(
			//     get_hitbox_based_on_transform_component(*grass_land.get_component<TransformComponent>())));
		}
	}

	auto player = m_game->create_entity();
	PlayerEntityBuilder{}.build_entity(player);
	player.add_components(std::make_unique<SolidComponent>(),
		std::make_unique<HealthPointsComponent>(),
		std::make_unique<BoundaryComponent>(
	    get_hitbox_based_on_transform_component(*player.get_component<TransformComponent>())),
		std::make_unique<DefaultCollisionArmorComponent>(),
		std::make_unique<TargetForDirectionComponent>());

	m_player_sprite = &player.get_component<SpriteComponent>()->sprite;
	m_player_sprite = m_player_sprite;
	place_entity(player.entity, {0.0f, 0.0f});

	auto mouse = m_game->create_entity();
	mouse.add_components(
		std::make_unique<SpriteComponent>(),
		std::make_unique<TransformComponent>(),
		std::make_unique<BoundaryComponent>(
	        get_hitbox_based_on_transform_component(*mouse.get_component<TransformComponent>())),
		std::make_unique<MouseComponent>(),
		std::make_unique<ElevationLevelComponent>(ElevationLevel::UI));

	mouse.get_component<TransformComponent>()->scale = {3, 3};
	auto& mouse_sprite = mouse.get_component<SpriteComponent>()->sprite;
	mouse_sprite.setTexture(*ResourceManager::get_instance()->get_texture(Textures::ID::CROSS_HAIR_DEFAULT));
	mouse.get_component<TransformComponent>()->size = {(float)mouse_sprite.getTextureRect().width,
	                                                   (float)mouse_sprite.getTextureRect().height};
}
