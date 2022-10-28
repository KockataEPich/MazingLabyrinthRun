#include "../include/animation/animation_player.h"
void AnimationPlayer::update(const FacingSide& side, float deltaTime) {
	m_total_time += deltaTime;
	if (m_total_time < m_current_animation.speed()) return;

	m_total_time -= m_current_animation.speed();
	if (m_current_animation.next_frame() && m_current_animation.reset_cycle())
		play_animation(Animation(get_idle_animation(m_skin, side)));
}