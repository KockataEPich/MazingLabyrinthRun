#ifndef ANIMATION_PLAYER_COMPONENT_HEADER
#define ANIMATION_PLAYER_COMPONENT_HEADER

#include "../animation/animation_player.h"

struct AnimationPlayerComponent : public Component<AnimationPlayerComponent> {
	explicit AnimationPlayerComponent(DefaultAnimations&& default_animations)
	    : m_animation_player{std::move(default_animations)} {};
	AnimationPlayer m_animation_player;
};

#endif