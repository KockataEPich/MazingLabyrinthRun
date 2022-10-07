#ifndef PLAYER_STATE_HEADER_H
#define PLAYER_STATE_HEADER_H

#include "../attribute/facingSide.h"
#include "../resource/skins.h"

struct PlayerState {
	FacingSide side;
	AnimationType currentAnimation;
};

#endif