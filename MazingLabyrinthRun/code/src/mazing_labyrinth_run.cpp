#include <mazing_labyrinth_run.h>

#include <animation/animation.h>
#include <entity_base/entity_handle.h>
#include <entity_creation/entity_builder/builders/grass_lands_tile_builder.h>
#include <entity_creation/entity_builder/builders/player_builder.h>
#include <entity_creation/entity_builder/builders/zombie_builder.h>
#include <resource/skins.h>
#include <resource/texture_enum.h>


#include <generated/systems/producer_systems/ai_system.h>
#include <generated/systems/producer_systems/animate_system.h>
#include <generated/systems/producer_systems/player_system.h>
#include <generated/systems/producer_systems/transform_system.h>
#include <generated/systems/producer_systems/update_crosshair_position_system.h>
#include <generated/systems/producer_systems/projectile_system.h>

#include <generated/systems/react_systems/collision_detection_system.h>
#include <generated/systems/react_systems/move_system.h>
#include <generated/systems/react_systems/attack_action_system.h>

#include <generated/systems/render_systems/render_sprite_system.h>
#include <generated/systems/render_systems/render_health_system.h>

#include <generated/systems/impulse_systems/basic_collision_system.h>
#include <generated/systems/impulse_systems/basic_damage_system.h>

#include <utils/component_utils.h>
#include <chrono>
#include <thread>

MazingLabyrinthRun::MazingLabyrinthRun() : m_window("MazingLabyrinthRun", sf::Vector2u(1920, 1080)) {
	initialize_game();
	restart_clock();
};

void MazingLabyrinthRun::initialize_game() {
	initialize_world();
	initialize_world_tiles();
	initialize_creatures();
	m_camera = sf::View({0.0f, 0.0f}, sf::Vector2f(m_window.get_window_size().x, m_window.get_window_size().y));
}

void MazingLabyrinthRun::initialize_world() {
	m_world = std::make_unique<World>(std::make_unique<EntityManager>());

	m_world->add_react_system(std::make_unique<MoveSystem>());
	m_world->add_react_system(std::make_unique<CollisionDetectionSystem>());
	m_world->add_react_system(std::make_unique<AttackActionSystem>());

	m_world->add_impulse_system(std::make_unique<BasicCollisionSystem>());
	m_world->add_impulse_system(std::make_unique<BasicDamageSystem>());

	m_world->add_producer_system(std::make_unique<PlayerSystem>(m_window))
	    ->add_producer_system(std::make_unique<AISystem>())
	    ->add_producer_system(std::make_unique<AnimateSystem>())
	    ->add_producer_system(std::make_unique<TransformSystem>())
	    ->add_producer_system(std::make_unique<ProjectileSystem>())
	    ->add_producer_system(std::make_unique<UpdateCrosshairPositionSystem>(m_window));

	m_world
		->add_render_system(std::make_unique<RenderSpriteSystem>(m_window))
		->add_render_system(std::make_unique<RenderHealthSystem>(m_window));

	m_world->init();
}

void MazingLabyrinthRun::initialize_world_tiles() {
	GrassLandsTileBuilder grass_builder;
	//ZombieEntityBuilder zombie_builder;
	//auto zombie = m_world->create_entity();
	//zombie_builder.build_entity(zombie);
	//zombie.add_component(std::make_unique<SolidComponent>());
	//zombie.add_component(std::make_unique<DefaultCollisionArmor>());
	//zombie.add_component(std::make_unique<HealthPointsComponent>());
	//zombie.add_component(std::make_unique<BoundaryComponent>(get_hitbox_based_on_transform_component(*zombie.get_component<TransformComponent>())));
	//m_world->place_entity(zombie, {64.0f, 64.0f});

	//auto zombie2 = m_world->create_entity();
	//zombie_builder.build_entity(zombie2);
	//zombie2.add_component(std::make_unique<SolidComponent>());
	//zombie2.add_component(std::make_unique<BoundaryComponent>(get_hitbox_based_on_transform_component(*zombie2.get_component<TransformComponent>())));
	//zombie2.add_component(std::make_unique<DefaultCollisionArmor>());
	//zombie2.add_component(std::make_unique<HealthPointsComponent>());
	//m_world->place_entity(zombie, {32.0f, 32.0f});
	
	for (int i = -1600; i <= 1600; i += 160) {
		for (int j = 1600; j >= -1600; j -= 160) {
			auto grass_land = m_world->create_entity();
			grass_builder.build_entity(grass_land);
			m_world->place_entity(grass_land, {(float)i, (float)j});
			//grass_land.add_component(std::make_unique<BoundaryComponent>(
			//    get_hitbox_based_on_transform_component(*grass_land.get_component<TransformComponent>())));
		}
	}
}

void MazingLabyrinthRun::initialize_creatures() {
	auto player = m_world->create_entity();
	PlayerEntityBuilder{}.build_entity(player);
	player.add_component(std::make_unique<SolidComponent>());
	player.add_component(std::make_unique<HealthPointsComponent>());
	player.add_component(std::make_unique<BoundaryComponent>(
	    get_hitbox_based_on_transform_component(*player.get_component<TransformComponent>())));
	player.add_component(std::make_unique<DefaultCollisionArmorComponent>());
	player.add_component(std::make_unique<TargetForDirectionComponent>());
	m_player_sprite = &player.get_component<SpriteComponent>()->sprite;
	m_world->set_player_location(m_player_sprite);
	m_world->place_entity(player, {0.0f, 0.0f});


	auto mouse = m_world->create_entity();
	mouse.add_component(std::make_unique<SpriteComponent>())
	    .add_component(std::make_unique<TransformComponent>())
	    .add_component(std::make_unique<BoundaryComponent>(
	        get_hitbox_based_on_transform_component(*mouse.get_component<TransformComponent>())))
	    .add_component(std::make_unique<MouseComponent>())
	    .add_component(std::make_unique<ElevationLevelComponent>(ElevationLevel::UI));


	mouse.get_component<TransformComponent>()->scale = {3, 3};
	auto& mouse_sprite = mouse.get_component<SpriteComponent>()->sprite;
	mouse_sprite.setTexture(*ResourceManager::get_instance()->get_texture(Textures::ID::CROSS_HAIR_DEFAULT));
	mouse.get_component<TransformComponent>()->size = {(float)mouse_sprite.getTextureRect().width,
	                                                     (float)mouse_sprite.getTextureRect().height};
}

void MazingLabyrinthRun::handle_input() {}

void MazingLabyrinthRun::update() {
	m_window.update();
	m_world->update(m_delta_time);
	// @TODO Can be used to pause the game
	m_camera.setCenter(m_player_sprite->getPosition());
	m_window.setView(m_camera);
}

void MazingLabyrinthRun::render() {
	m_window.begin_draw();
	m_world->render();

	m_window.end_draw();
}

void MazingLabyrinthRun::start_game() {
	while (!m_window.is_done()) {
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		m_delta_time = m_elapsed.asSeconds();
		handle_input();
		update();
		render();
		restart_clock();
	}
}