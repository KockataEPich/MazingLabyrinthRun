// ################## THIS FILE IS GENERATED ##################
#ifndef ANIMATION_PLAYER_COMPONENT_HEADER
#define ANIMATION_PLAYER_COMPONENT_HEADER

#include <component_base/component.h>
#include <animation/animation_player.h>

struct AnimationPlayerComponent : public Component<AnimationPlayerComponent> {
	AnimationPlayerComponent() = default;
	explicit AnimationPlayerComponent(
		AnimationPlayer&& animation_player) : 
		animation_player{animation_player}{}

	AnimationPlayer animation_player;
};
#endif