#include <mazing_labyrinth_run.h>

#include <chrono>
#include <thread>

MazingLabyrinthRun::MazingLabyrinthRun() : m_window("MazingLabyrinthRun", sf::Vector2u(1920, 1080)) {
	initialize_game();
	restart_clock();
};

void MazingLabyrinthRun::initialize_game() {
	m_game = std::make_unique<Game>(&m_window);
	m_game->init();
}

void MazingLabyrinthRun::handle_input() {}

void MazingLabyrinthRun::update() {
	m_window.update();
	m_game->systems->update(m_delta_time);
	// @TODO Can be used to pause the game
	m_camera.setCenter(m_player_sprite->getPosition());
	m_window.setView(m_camera);
}

void MazingLabyrinthRun::render() {
	m_window.begin_draw();
	m_game->systems->render();
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