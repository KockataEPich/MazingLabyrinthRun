#include "../include/mazingLabyrinthRun.h"
#include "../include/game.h"
#include "../include/tile/tileMap.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void MazingLabyrinthRun::start_game() {

	// create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Tilemap");

	// define the level with an array of tile indices
	const int level[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0,
						 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 1,
						 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1,
						 1, 1, 2, 0, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 2, 0, 1, 0,
						 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1,
						 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 2, 1, 2, 3,
						 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2,
						 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 2, 1, 2, 3};

	// create the tilemap from the level definition
	TileMap map;
	if(!map.load("C:/Personal/MazingLabyrinthRun/MazingLabyrinthRun/build/Debug/tileset.png",
				 sf::Vector2u(32, 32),
				 level,
				 16,
				 8))
		return;

	// run the main loop
	while(window.isOpen()) {
		// handle events
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// draw the map
		window.clear();
		window.draw(map);
		window.display();
	}

	//sf::RenderWindow window(sf::VideoMode(1280, 720), "MazingLabyrinthRun");

	//Game mazingLabyrinthRun;
	//mazingLabyrinthRun.fill_map();

	//while(window.isOpen()) {
	//	sf::Event event;
	//	while(window.pollEvent(event)) {
	//		if(event.type == sf::Event::Closed)
	//			window.close();
	//	}
	//	window.clear(sf::Color::White);
	//	for(auto& tile : mazingLabyrinthRun.m_tiles)
	//		window.draw(*tile.get());
	//	window.display();
	//}
}