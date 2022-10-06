#ifndef PLAYER_STATE_HEADER_H
#define PLAYER_STATE_HEADER_H

#include "../attribute/facingSide.h"

enum class PlayerAnimation {default_animation, run};

struct PlayerState {
	FacingSide side;
	PlayerAnimation currentAnimation;
};

#endif