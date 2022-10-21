#include "../include/animation/animation.h"

bool Animation::next_frame() {
	m_current_rectange.left += m_x_axis_offset;
	if (m_current_rectange.left == m_texture->getSize().x) { return true; }

	return false;
}

bool Animation::reset_cycle() {
	if (m_repeat.number_of_times == -1) {
		m_current_rectange.left = 0;
		return false;
	}

	if (--m_repeat.number_of_times == 0) return true;

	m_current_rectange.left = 0;
	return false;
}

bool operator==(const Animation& lhs, const Animation& rhs) { return lhs.m_texture_id == rhs.m_texture_id; }