#ifndef MOVING_STATE_HEADER_H
#define MOVING_STATE_HEADER_H

#include "../attribute/facingSide.h"
#include "../../complexWorldObject/active_object_state.h"
struct MovableState : ActiveObjectState{
	FacingSide side;
	float speed;
};

#endif