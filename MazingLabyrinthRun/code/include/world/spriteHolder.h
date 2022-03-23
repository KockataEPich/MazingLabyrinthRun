#ifndef SPRITE_HOLDER_HEADER_H
#	define SPRITE_HOLDER_HEADER_H

#include "../world/iWorldObject.h"

#include <memory>

class SpriteHolder {
public:
	SpriteHolder();

private:
	std::unordered_map<,std::unique_ptr<IWorldObject>> m_all_world_objects;


};

#endif