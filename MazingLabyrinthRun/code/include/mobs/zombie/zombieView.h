#ifndef ZOMBIE_VIEW_HEADER_H
#define ZOMBIE_VIEW_HEADER_H

#include "../include/animation/animationPlayer.h"
#include "../include/entityBase/view/animated_view.h"
#include "zombie_state.h"

class ZombieView : public AnimatedView<ZombieState> {
public:
	ZombieView();
};

#endif