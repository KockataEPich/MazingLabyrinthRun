#ifndef ANIMATION_PLAYER_HEADER_H
#define ANIMATION_PLAYER_HEADER_H

#include "../include/resource/resourceManager.h"
#include "../include/attribute/facingSide.h"
#include <SFML/Graphics/Sprite.hpp>
#include "animation.h"
#include "default_animations.h"

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class AnimationPlayer {
public:
	AnimationPlayer(DefaultAnimations&& defaultAnimations);

	sf::Texture& getCurrentTexture(){ return *m_currentAnimation.getTexture(); };
	Animation& getCurrentAnimation(){ return m_currentAnimation; };

	void playAnimation(Animation&& animation);
	void AnimationPlayer::playAnimation(Animation& animation);

	void update(const FacingSide& side, float deltaTime);
	void playDefaultAnimation(const FacingSide& side);
	sf::IntRect& get_current_rect();

private:
	float m_totalTime = 0.0f;
	DefaultAnimations m_defaultAnimations;
	Animation m_currentAnimation;
};

#endif

