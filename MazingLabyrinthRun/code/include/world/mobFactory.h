#ifndef MOVING_OBJECT_HEADER_H
#define MOVING_OBJECT_HEADER_H

#include "iWorldObject.h"

class MovingObject : public IWorldObject {

public:
	virtual void move(const float delta) = 0;

protected:
	float m_movementSpeed;
};

#endif