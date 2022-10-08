#ifndef MOVING_STATE_HEADER_H
#define MOVING_STATE_HEADER_H

#include "../attribute/facingSide.h"

struct MovableState {
	FacingSide side;
	float speed;
	float delta_time;
};

#endif