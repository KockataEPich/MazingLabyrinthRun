#ifndef PLAYER_VIEW_HEADER_H
#define PLAYER_VIEW_HEADER_H

#include "../include/animation/animationPlayer.h"
#include "../include/entityBase/view/animated_view.h"
#include "player_state.h"

class PlayerView : public AnimatedView<PlayerState> {
public:
	PlayerView();
};

#endif