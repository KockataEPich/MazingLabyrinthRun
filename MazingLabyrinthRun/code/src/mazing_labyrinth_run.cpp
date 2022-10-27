#include "../include/mazing_labyrinth_run.h"

#include "../include/animation/animation.h"
#include "../include/entity_base/entity_handle.h"
#include "../include/resource/skins.h"
#include "../include/resource/texture_enum.h"
#include "../include/system/systems/animate_system.h"
#include "../include/system/systems/move_system.h"
#include "../include/system/systems/player_system.h"
#include "../include/system/systems/render_system.h"
#include "../include/system/systems/transform_system.h"
#include "../include/factory/entity_factory.h"
MazingLabyrinthRun::MazingLabyrinthRun() : m_window("MazingLabyrinthRun", sf::Vector2u(1920, 1080)) {
	initialize_game();
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
	m_world->add_system(std::make_unique<Player>());
	m_world->add_system(std::make_unique<Animate>());
	m_world->add_system(std::make_unique<Transform>());

	m_world->init();
}

void MazingLabyrinthRun::initialize_world_tiles() {
	tile_texture.loadFromFile("resources/tile/grass.png");

	for (int i = -1600; i <= 1600; i += 160) {
		for (int j = 1600; j >= -1600; j -= 160) {
			auto grass_land = m_world->create_entity();

			sf::Sprite grass;
			grass.setPosition(sf::Vector2f((float)i, (float)j));
			grass.setTexture(tile_texture);
			grass.scale(sf::Vector2f(5.0f, 5.0f));
			grass.setPosition(i, j);

			grass_land.add_component(std::make_unique<SpriteComponent>(std::move(grass)));
		}
	}
}

void MazingLabyrinthRun::initialize_creatures() {
	auto player = m_world->create_entity();
	create_entity_type(EntityType::player, player);
	m_player_sprite = &player.get_component<SpriteComponent>()->m_sprite;
}

void MazingLabyrinthRun::handle_input() {}

void MazingLabyrinthRun::update() {
	m_window.update();
	m_world->update(m_deltaTime);
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
		m_deltaTime = m_elapsed.asSeconds();
		handle_input();
		update();
		render();
		restart_clock();
	}
}