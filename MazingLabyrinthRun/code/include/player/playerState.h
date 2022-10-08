#ifndef PLAYER_STATE_HEADER_H
#define PLAYER_STATE_HEADER_H

#include "../entityBase/logic/movable_logic/default_movable_state.h"
#include "../resource/skins.h"

struct PlayerState : public MovableState {
	AnimationType currentAnimation;
};

#endif