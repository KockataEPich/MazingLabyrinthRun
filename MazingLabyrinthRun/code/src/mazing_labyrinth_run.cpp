#include "../include/mazing_labyrinth_run.h"

#include "../include/animation/animation.h"
#include "../include/entity_base/entity_handle.h"
#include "../include/entity_creation/entity_builder/builders/grass_lands_tile_builder.h"
#include "../include/entity_creation/entity_builder/builders/player_builder.h"
#include "../include/entity_creation/entity_builder/builders/zombie_builder.h"
#include "../include/resource/skins.h"
#include "../include/resource/texture_enum.h"
#include "../include/system/systems/ai_system.h"
#include "../include/system/systems/animate_system.h"
#include "../include/system/systems/event_system.h"
#include "../include/system/systems/move_system.h"
#include "../include/system/systems/player_system.h"
#include "../include/system/systems/render_system.h"
#include "../include/system/systems/transform_system.h"

#include <system/systems/ai_system.h>

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

	m_world->add_render_system(std::make_unique<Render>(m_window));
	// TODO this is insanely ugly. I need go find a way to fix this
	m_world->add_system(std::make_unique<Player>())
	    ->add_system(std::make_unique<Animate>())
	    ->add_system(std::make_unique<Transform>())
	    ->add_system(std::make_unique<AI>())
	    ->add_system(std::make_unique<EventSystem>())
	    ->add_system(std::make_unique<Move>());

	m_world->init();
}

void MazingLabyrinthRun::initialize_world_tiles() {
	GrassLandsTileBuilder grass_builder;
	ZombieEntityBuilder zombie_builder;
	auto zombie = m_world->create_entity();
	zombie_builder.build_entity(zombie);
	m_world->place_entity(zombie, {64.0f, 64.0f});
	
	for (int i = -1600; i <= 1600; i += 160) {
		for (int j = 1600; j >= -1600; j -= 160) {
			auto grass_land = m_world->create_entity();
			grass_builder.build_entity(grass_land);
			m_world->place_entity(grass_land, {(float)i, (float)j});
		}
	}
}

void MazingLabyrinthRun::initialize_creatures() {
	auto player = m_world->create_entity();
	PlayerEntityBuilder{}.build_entity(player);
	player.add_component(std::make_unique<StatusListComponent>());

	m_player_sprite = &player.get_component<SpriteComponent>()->m_sprite;
	m_world->set_player_location(m_player_sprite);
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