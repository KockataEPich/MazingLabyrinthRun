#ifndef MOVING_OBJECT_HEADER_H
#define MOVING_OBJECT_HEADER_H
#include "default_movable_state.h"

#include <type_traits>

class Movable {
public:
	virtual void move(const float delta) = 0;
};

#endif