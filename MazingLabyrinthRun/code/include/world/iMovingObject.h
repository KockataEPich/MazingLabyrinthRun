#ifndef MOVING_OBJECT_HEADER_H
#define MOVING_OBJECT_HEADER_H

#include "iWorldObject.h"

class IMovingObject : public IWorldObject {

public:
	virtual void move(const float delta) = 0;

protected:
	float m_speed;
};

#endif