#ifndef PLAYER_STATE_HEADER_H
#define PLAYER_STATE_HEADER_H

#include "../entityBase/logic/movable_logic/movable_state.h"
#include "../resource/skins.h"

struct PlayerState : MovableState{
	std::string todo_remove;
};

#endif