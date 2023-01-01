#include "../include/animation/animation.h"

bool Animation::next_frame() {
	m_current_rectange.left += m_x_axis_offset;
	return m_current_rectange.left == m_texture->getSize().x;
}

bool Animation::reset_cycle() {
	if (!m_number_of_cycles.has_value() || m_number_of_cycles.value()-- == 0) return true;
	m_current_rectange.left = 0;
	return false;
}

bool operator==(const Animation& lhs, const Animation& rhs) { return lhs.m_texture_id == rhs.m_texture_id; }

void Animation::operator=(Animation& other) noexcept {
	m_x_axis_offset = other.m_x_axis_offset;
	m_texture_id = other.m_texture_id;
	m_number_of_cycles = other.m_number_of_cycles;
	m_speed = other.m_speed;
	m_texture = other.m_texture;
	m_current_rectange = sf::IntRect{0, 0, other.m_x_axis_offset, (int)m_texture->getSize().y};
}