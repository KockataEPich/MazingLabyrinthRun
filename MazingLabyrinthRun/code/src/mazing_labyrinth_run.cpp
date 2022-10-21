#include "../include/mazing_labyrinth_run.h"

#include "../include/entity_base/entity_handle.h"
#include "../include/system/systems/render_system.h"

MazingLabyrinthRun::MazingLabyrinthRun() : m_window("MazingLabyrinthRun", sf::Vector2u(1920, 1080)) {
	initialize_game();
};

void MazingLabyrinthRun::initialize_game() {
	tile_texture.loadFromFile("resources/tile/grass.png");

	m_world = std::make_unique<World>(std::make_unique<EntityManager>());

	std::unique_ptr<System> render = std::make_unique<Render>(m_window);
	m_world->add_system(std::move(render));

	m_world->init();
	m_camera =
	    sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_window.get_window_size().x, m_window.get_window_size().y));

	for (int i = -1600; i <= 1600; i += 160) {
		for (int j = 1600; j >= -1600; j -= 160) {
			auto grass_land = m_world->create_entity();

			sf::Sprite processed_tile;
			processed_tile.setPosition(sf::Vector2f((float)i, (float)j));
			processed_tile.setTexture(tile_texture);
			processed_tile.scale(sf::Vector2f(5.0f, 5.0f));
			processed_tile.setPosition(i, j);

			grass_land.add_component(std::make_unique<SpriteComponent>(std::move(processed_tile)));
		}
	}
}

void MazingLabyrinthRun::handle_input() {}

void MazingLabyrinthRun::update() {
	m_window.update();
	m_world->update(m_deltaTime);
	// m_camera.setCenter(m_player->getPosition());
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