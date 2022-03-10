#include "../include/mazingLabyrinthRun.h"
#include "../include/game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

void MazingLabyrinthRun::start_game() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "MazingLabyrinthRun");

	Game mazingLabyrinthRun;

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
		}
		if(event.type == sf::Event::Closed)
			window.close();

		mazingLabyrinthRun.update();

		for(auto& rows : mazingLabyrinthRun.display_matrix())
			for(auto& tile : rows)
				window.draw(tile);

		window.display();
	}
}