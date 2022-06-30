#ifndef COMPOUND_WORLD_OBJECT_HEADER_H
#define COMPOUND_WORLD_OBJECT_HEADER_H

#include "../include/entityBase/component/componentMap.h"
#include "../include/entityBase/component/componentSprite.h"
#include "../include/entityBase/worldObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <unordered_map>

template<typename T>
class CompoundWorldObject : public virtual WorldObject {
public:
	CompoundWorldObject() {}
	ComponentSpriteMap<T>* componentsMap() { return &m_components; }

protected:
	ComponentSpriteMap<T> m_components;
	virtual void initializeComponentSpriteMap() = 0;
};

#endif