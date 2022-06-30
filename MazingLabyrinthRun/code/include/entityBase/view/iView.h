#ifndef I_VIEW_HEADER_H
#define I_VIEW_HEADER_H

#include <SFML/Graphics/Sprite.hpp>
#include "../include/entityBase/complexWorldObject/borrowSpriteObject.h"

template<typename T>
class IView : public BorrowSpriteObject{
public:
	virtual void update(const T* state, const float deltaTime) = 0;
	virtual void initialize() = 0;
};

#endif