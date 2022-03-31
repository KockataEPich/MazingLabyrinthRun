#ifndef WORLD_OBJECT_HOLDER_HEADER_H
#define WORLD_OBJECT_HOLDER_HEADER_H

#include "../world/iWorldObject.h"
#include "tile/tileFactory.h"

#include <memory>
#include <vector>

class WorldObjectHolder {
public:
	WorldObjectHolder();

	std::vector<std::unique_ptr<IWorldObject>>& getAllWorldObjects() { return m_allWorldObjects; }
	void add_to_world_objects(const IWorldObject& worldObject) {
		m_allWorldObjects.push_back(std::make_unique<IWorldObject>(worldObject));
	}

	void initializeWorld(const sf::Vector2u& window_size);

private:
	std::vector<std::unique_ptr<IWorldObject>> m_allWorldObjects;

	//TextureManager m_textureManager;
	//TileFactory m_tileFactory{m_textureManager};
};

#endif