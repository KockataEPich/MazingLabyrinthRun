#ifndef I_LOGIC_HEADER_H
#define I_LOGIC_HEADER_H

#include <SFML/Graphics/Sprite.hpp>
#include "../include/entityBase/complexWorldObject/borrowSpriteObject.h"

template<typename T>
class ILogic : public BorrowSpriteObject {
public:
	virtual T* doLogic(const float deltaTime) = 0;
	virtual void initialize() = 0;

protected:
	T m_state;
};

#endif