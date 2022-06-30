#ifndef MOVING_OBJECT_HEADER_H
#define MOVING_OBJECT_HEADER_H

#include "../include/entityBase/worldObject.h"
#include "../include/attribute/facingSide.h"

class Movable {
public:
	virtual void move(const float delta) = 0;

protected:
	float m_speed;
	FacingSide m_facingSide;
};

#endif