#include "../include/tile/iTile.h"
#include "../include/tile/path.h"
#include "../include/tile/wall.h"
#include "../include/tile/tileEnum.h"
#include "../include/tile/tileFactory.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <memory>

class Game {
public:
	Game();
	void update();
	std::vector<std::unique_ptr<ITile>> m_tiles;
	void fill_map();

private:
	TileFactory tileFactory;

	
	void process_tile(const TileType& type);

	

};