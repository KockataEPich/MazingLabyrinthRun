#include "../include/animation/animation.h"

void Animation::nextFrame() {
	m_frameIndex++;
	if (m_frameIndex == m_frames->size()) throw EndAnimationException("The end of the animation has been reached");
}

void Animation::resetAnimation() {
	m_frameIndex = 0;
	m_timesPlayed++;
}

bool Animation::animationCycleFinish() {
	if (m_repeatNumber == -1) return false;
	if (m_timesPlayed < m_repeatNumber) return false;
	return true;
}

bool Animation::operator==(const Animation animation) {
	if (m_name == animation.m_name) return true;
	return false;
}

void Animation::operator=(const Animation animation) {
	m_name = animation.m_name;
	m_frames = animation.m_frames;
	m_repeatNumber = animation.m_repeatNumber;
	m_speed = animation.m_speed;

	m_timesPlayed = 0;
	m_frameIndex = 0;
}