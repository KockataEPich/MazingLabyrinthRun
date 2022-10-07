#include "../include/animation/animationPlayer.h"

AnimationPlayer::AnimationPlayer(DefaultAnimations&& defaultAnimations)
    : m_defaultAnimations{defaultAnimations}
    , m_currentAnimation{m_defaultAnimations.facingDown} {}

void AnimationPlayer::playAnimation(Animation& animation) {
	if(m_currentAnimation == animation)
		return;
	m_currentAnimation = animation;
}

void AnimationPlayer::update(const FacingSide& side, float deltaTime) {
	m_totalTime += deltaTime;

	if (m_totalTime >= m_currentAnimation.speed()) {
		m_totalTime -= m_currentAnimation.speed();

		if (m_currentAnimation.nextFrame() && m_currentAnimation.resetCycle()) playDefaultAnimation(side);
	}
}
sf::IntRect& AnimationPlayer::get_current_rect() { return m_currentAnimation.get_current_rect(); }

void AnimationPlayer::playDefaultAnimation(const FacingSide& side) {
	switch (side) {
		case FacingSide::down: playAnimation(m_defaultAnimations.facingDown); break;
		case FacingSide::up: playAnimation(m_defaultAnimations.facingUp); break;
		case FacingSide::left: playAnimation(m_defaultAnimations.facingLeft); break;
		case FacingSide::right: playAnimation(m_defaultAnimations.facingRight); break;
	}
}