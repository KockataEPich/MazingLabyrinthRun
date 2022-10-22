#ifndef ANIMATION_PLAYER_HEADER_H
#define ANIMATION_PLAYER_HEADER_H

#include "../include/attribute/facingSide.h"
#include "animation.h"
#include "default_animations.h"

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class AnimationPlayer {
public:
	AnimationPlayer(DefaultAnimations&& default_animations);

	sf::Texture& get_current_texture(){ return *m_current_animation.get_texture(); };
	Animation& get_current_animation(){ return m_current_animation; };

	void play_animation(Animation&& animation);
	void play_animation(Animation& animation);

	void update(const FacingSide& side, float deltaTime);
	void play_default_animation(const FacingSide& side);
	sf::IntRect& get_current_rect();

private:
	float m_total_time = 0.0f;
	DefaultAnimations m_default_animations;
	Animation m_current_animation;
};

#endif

