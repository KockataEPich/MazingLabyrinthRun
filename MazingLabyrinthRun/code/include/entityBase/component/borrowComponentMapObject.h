#ifndef BORROW_COMPONENT_MAP_OBJECT_HEADER_H
#define BORROW_COMPONENT_MAP_OBJECT_HEADER_H

#include "ComponentMap.h"

template<typename T>
class BorrowComponentSpriteMapObject {
public:
	BorrowComponentSpriteMapObject(ComponentSpriteMap<T>* components) : m_components{components} {}

protected:
	ComponentSpriteMap<T>* m_components;
};

#endif