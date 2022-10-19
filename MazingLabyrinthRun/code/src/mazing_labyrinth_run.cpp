#include "../include/mazing_labyrinth_run.h"
#include "../include/entity_base/entity_handle.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace {

struct Position : Component<Position> {
	Position(float x) : x(x){};
	float x;
};

class Wind : public System {
public:
	Wind() { m_signature.add_component<Position>(); }

	void update(float dt) override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<Position> position;
			m_parent_world->unpack(entity, position);

			position->x += 1.0f * (dt / 1000.0f);
		}
	}
};

void test_ECS(float m_deltaTime) {
	auto entityManager = std::make_unique<EntityManager>();
	auto world = std::make_unique<World>(std::move(entityManager));

	std::unique_ptr<System> wind = std::make_unique<Wind>();
	world->add_system(std::move(wind));

	world->init();

	auto tumbleweed = world->create_entity();
	tumbleweed.add_component(Position(0));

	for (int i = 0; i < 50; i++) { world->update(m_deltaTime); }
}
}  // namespace

MazingLabyrinthRun::MazingLabyrinthRun() : m_window("MazingLabyrinthRun", sf::Vector2u(1920, 1080)) {
	initialize_game();

	tile_texture.loadFromFile("resources/tile/grass.png");

	for (int i = -1600; i <= 1600; i += 160) {
		for (int j = 1600; j >= -1600; j -= 160) {
			sf::Sprite tile;
			tile.setPosition(sf::Vector2f((float)i, (float)j));
			tile.setTexture(tile_texture);
			tile.scale(sf::Vector2f(5.0f, 5.0f));
			grass_lands.push_back(tile);
		}
	}
};

void MazingLabyrinthRun::initialize_game() {
	m_world = std::make_unique<World>(std::make_unique<EntityManager>());
	m_world->init();
	m_camera = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_window.get_window_size().x, m_window.get_window_size().y));
}

void MazingLabyrinthRun::handle_input() {}

void MazingLabyrinthRun::update() {
	m_window.update();
	m_world->update(m_deltaTime);
	// m_camera.setCenter(m_player->getPosition());
	m_window.setView(m_camera);
	test_ECS(m_deltaTime);
}

void MazingLabyrinthRun::render() {
	m_world->render();
	m_window.begin_draw();
	for (auto& grass : grass_lands) m_window.draw(grass);

	m_window.end_draw();
}

void MazingLabyrinthRun::start_game() {
	while (!m_window.is_done()) {
		m_deltaTime = get_elapsed().asSeconds();
		handle_input();
		update();
		render();
		restart_clock();
	}
}