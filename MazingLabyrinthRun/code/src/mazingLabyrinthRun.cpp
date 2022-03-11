#include "../include/mazingLabyrinthRun.h"
#include "../include/game.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void MazingLabyrinthRun::start_game() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "MazingLabyrinthRun");

	Game mazingLabyrinthRun;
	mazingLabyrinthRun.fill_map();

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		for(auto& tile : mazingLabyrinthRun.m_tiles)
			window.draw(*tile.get());
		window.display();
	}
}