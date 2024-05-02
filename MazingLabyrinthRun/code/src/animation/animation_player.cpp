#include "../include/animation/animation_player.h"

#include <time/time_manager.h>

void AnimationPlayer::update(const FacingSide& side) {
	remove_flashing_if_finished();
	if (++m_total_time < m_current_animation.speed()) return;

	m_total_time -= m_current_animation.speed();
	if (m_current_animation.next_frame() && m_current_animation.reset_cycle())
		play_animation(Animation(get_idle_animation(m_skin)));
}

void AnimationPlayer::remove_flashing_if_finished() {
	if (!m_flash_white) return;
	if (TimeManager::get_instance()->is_job_done("Zombie Flashing White")) { 
		m_skin = get_unflashed_skin(m_skin);
		m_flash_white = false;
	}
}

void AnimationPlayer::flash_white() { 
	TimeManager::get_instance()->track_job("Zombie Flashing White", 0.2);
	m_flash_white = true; 
}