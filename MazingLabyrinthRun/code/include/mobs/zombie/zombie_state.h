#ifndef ZOMBIE_STATE_HEADER_H
#define ZOMBIE_STATE_HEADER_H

#include "../../entityBase/logic/movable_logic/movable_state.h"
#include "../../resource/skins.h"

struct ZombieState : MovableState {
	std::string todo_remove;
};

#endif