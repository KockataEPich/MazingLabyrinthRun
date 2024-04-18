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
	m_camera = sf::View({0.0f, 0.0f}, sf::Vector2f(m_window.get_window_size().x, m_window.get_window_size().y));
}

void MazingLabyrinthRun::handle_input() {}

void MazingLabyrinthRun::update() {
	m_window.begin_draw();
	m_window.update();
	m_game->systems->update(m_delta_time);
	// @TODO Can be used to pause the game
	m_camera.setCenter(m_game->world->get_player_sprite().getPosition());
	m_window.setView(m_camera);
	m_game->update_mouse_position();
}

void MazingLabyrinthRun::render() {
	m_game->systems->render();
	m_window.end_draw();
}

void MazingLabyrinthRun::start_game() {
	while (!m_window.is_done()) {
		// std::this_thread::sleep_for(std::chrono::milliseconds(100));
		sf::Event event;
		m_window.as_sfml_window().pollEvent(event);

		if (event.type == sf::Event::LostFocus) m_window.m_is_in_focus = false;
		if (event.type == sf::Event::GainedFocus) m_window.m_is_in_focus = true;

		m_delta_time = m_elapsed.asSeconds();

		if (m_window.m_is_in_focus) {
			handle_input();
			update();
			render();
		}
		restart_clock();
	}
}