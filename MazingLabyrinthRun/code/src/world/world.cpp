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
	auto player = m_game->create_entity();
	PlayerEntityBuilder{}.build_entity(player);
	player.add_components<SolidComponent,
	                      HealthPointsComponent,
	                      DefaultCollisionArmorComponent,
	                      VelocityComponent,
	                      BoundaryComponent>();
	m_player_sprite = &player.get_component<SpriteComponent>()->sprite;
	m_player_sprite = m_player_sprite;
	place_entity(player.entity, {0.0f, 0.0f});
	player.add_event_components<UpdateBoundaryFromTransformComponent>();
	
	GrassLandsTileBuilder grass_builder;
	ZombieEntityBuilder zombie_builder;

	auto zombie = m_game->create_entity();
	zombie_builder.build_entity(zombie);
	m_game->world->place_entity(zombie.entity, {100.0f, 100.0f});
	zombie.add_components<BoundaryComponent>();

	for (int i = -1600; i <= 1600; i += 160) {
		 int counter = 0;
		 for (int j = 1600; j >= -1600; j -= 160) {
			 auto grass_land = m_game->create_entity();
			 grass_builder.build_entity(grass_land);
			 place_entity(grass_land.entity, {(float)i, (float)j});
			 grass_land.add_components(std::make_unique<SkinComponent>(Skin::GRASS_LANDS_1));
			 grass_land.add_components<BoundaryComponent>();

			 if (i == 0 && j == 0) continue;
			 if (counter == 20) {

				 auto zombie = m_game->create_entity();
				 zombie_builder.build_entity(zombie);

				 m_game->world->place_entity(zombie.entity, {(float)i, (float)j});
				 zombie.add_components<BoundaryComponent>();
				 counter = 0;
			 }
			 counter++;
		 }
	}

	std::unique_ptr<TransformComponent> mouse_transform = std::make_unique<TransformComponent>(); 
	auto mouse = m_game->create_entity();
	mouse.add_components<SpriteComponent, MouseComponent>();
	mouse.add_components(std::move(mouse_transform),
						 std::make_unique<ElevationLevelComponent>(ElevationLevel::UI),
	                     std::make_unique<SkinComponent>(Skin::CROSSHAIR_DEFAULT_SKIN));
	
	mouse.get_component<TransformComponent>()->scale = {3, 3};
	auto& mouse_sprite = mouse.get_component<SpriteComponent>()->sprite;
	mouse_sprite.setTexture(*ResourceManager::get_instance()->get_texture(Textures::ID::CROSS_HAIR_DEFAULT));
	mouse.get_component<TransformComponent>()->size = {(float)mouse_sprite.getTextureRect().width,
	                                                   (float)mouse_sprite.getTextureRect().height};
	mouse_sprite.setOrigin(
	    {(float)mouse_sprite.getTextureRect().width / 2.0f, (float)mouse_sprite.getTextureRect().height / 2.0f});
	mouse.add_components<BoundaryComponent>();
	m_game->quad_tree->remove(mouse.entity);
}
