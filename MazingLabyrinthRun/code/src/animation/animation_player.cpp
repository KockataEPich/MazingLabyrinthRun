#include "../include/animation/animation_player.h"

AnimationPlayer::AnimationPlayer(DefaultAnimations&& defaultAnimations)
    : m_default_animations{defaultAnimations}
    , m_current_animation{m_default_animations.facingDown} {}

void AnimationPlayer::play_animation(Animation&& animation) { m_current_animation = animation; }
void AnimationPlayer::play_animation(Animation& animation) { m_current_animation = animation; }

void AnimationPlayer::update(const FacingSide& side, float deltaTime) {
	m_total_time += deltaTime;

	if (m_total_time >= m_current_animation.speed()) {
		m_total_time -= m_current_animation.speed();

		if (m_current_animation.next_frame() && m_current_animation.reset_cycle()) play_default_animation(side);
	}
}
sf::IntRect& AnimationPlayer::get_current_rect() { return m_current_animation.get_current_rect(); }

void AnimationPlayer::play_default_animation(const FacingSide& side) {
	switch (side) {
		case FacingSide::down: play_animation(m_default_animations.facingDown); break;
		case FacingSide::up: play_animation(m_default_animations.facingUp); break;
		case FacingSide::left: play_animation(m_default_animations.facingLeft); break;
		case FacingSide::right: play_animation(m_default_animations.facingRight); break;
	}
}