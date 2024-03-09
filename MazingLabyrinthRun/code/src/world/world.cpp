#include <world/world.h>
#include <game.h>

#include <generated/components/data_components/transform_component.h>
#include <entity_base/entity_handle.h>
#include <entity_creation/entity_builder/builders/grass_lands_tile_builder.h>
#include <entity_creation/entity_builder/builders/zombie_builder.h>
#include <entity_creation/entity_builder/builders/player_builder.h>

#include <generated/components/data_components/boundary_component.h>
#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/velocity_component.h>
#include <generated/components/data_components/health_points_component.h>
#include <generated/components/data_components/elevation_level_component.h>

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
	zombie2.add_components <SolidComponent,
							DefaultCollisionArmorComponent,
							VelocityComponent,
							HealthPointsComponent>();

	m_game->world->place_entity(zombie2.entity, {100.0f, 100.0f});
	zombie2.add_components(std::make_unique<BoundaryComponent>(
	    get_hitbox_based_on_transform_component(*zombie2.get_component<TransformComponent>())));

	
	/*
	 for (int i = -1600; i <= 1600; i += 160) {
		int counter = 0;
		for (int j = 1600; j >= -1600; j -= 160) {
			// auto grass_land = m_game->create_entity();
			// grass_builder.build_entity(grass_land);
			if (i == 0 && j == 0) 
				continue;
			if (counter == 20) {
				
			    auto zombie = m_game->create_entity();
			    zombie_builder.build_entity(zombie);
			    zombie.add_components<SolidComponent,
									  DefaultCollisionArmorComponent,
									  HealthPointsComponent,
									  VelocityComponent>();

			    m_game->world->place_entity(zombie.entity, {(float)i, (float)j});
				zombie.add_components(std::make_unique<BoundaryComponent>(
				    get_hitbox_based_on_transform_component(*zombie.get_component<TransformComponent>())));
			    counter = 0;
			}
			counter++;
			// place_entity(grass_land.entity, {(float)i, (float)j});

			// grass_land.add_component(std::make_unique<BoundaryComponent>(
			//     get_hitbox_based_on_transform_component(*grass_land.get_component<TransformComponent>())));
		}
	}*/
	

	auto player = m_game->create_entity();
	PlayerEntityBuilder{}.build_entity(player);
	player.add_components<SolidComponent,
	                      HealthPointsComponent,
	                      DefaultCollisionArmorComponent,
	                      VelocityComponent>();

	player.add_components(
		std::make_unique<BoundaryComponent>(get_hitbox_based_on_transform_component(*player.get_component<TransformComponent>())));

	m_player_sprite = &player.get_component<SpriteComponent>()->sprite;
	m_player_sprite = m_player_sprite;
	place_entity(player.entity, {0.0f, 0.0f});

	std::unique_ptr<TransformComponent> mouse_transform = std::make_unique<TransformComponent>(); 
	auto mouse = m_game->create_entity();
	mouse.add_components<SpriteComponent, MouseComponent, HealthPointsComponent>();
	mouse.add_components(
		std::make_unique<BoundaryComponent>(get_hitbox_based_on_transform_component(*mouse_transform)),
	                     std::move(mouse_transform),
						 std::make_unique<ElevationLevelComponent>(ElevationLevel::UI));

	mouse.get_component<TransformComponent>()->scale = {3, 3};
	auto& mouse_sprite = mouse.get_component<SpriteComponent>()->sprite;
	mouse_sprite.setTexture(*ResourceManager::get_instance()->get_texture(Textures::ID::CROSS_HAIR_DEFAULT));
	mouse.get_component<TransformComponent>()->size = {(float)mouse_sprite.getTextureRect().width,
	                                                   (float)mouse_sprite.getTextureRect().height};
}
