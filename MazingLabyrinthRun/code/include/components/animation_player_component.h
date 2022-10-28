#ifndef ANIMATION_PLAYER_COMPONENT_HEADER
#define ANIMATION_PLAYER_COMPONENT_HEADER

#include "../animation/animation_player.h"

struct AnimationPlayerComponent : public Component<AnimationPlayerComponent> {
	AnimationPlayer m_animation_player;
};

#endif