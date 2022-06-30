#include "../include/animation/animationPlayer.h"

AnimationPlayer::AnimationPlayer(DefaultAnimations& defaultAnimations) : m_defaultAnimations{defaultAnimations} {
	playAnimation(m_defaultAnimations.facingRight);
}

void AnimationPlayer::playAnimation(Animation& animation) {
	if (m_currentAnimation == animation) return;
	m_currentAnimation = animation;
	updateCurrentTexture();
}

void AnimationPlayer::update(const FacingSide& side, float deltaTime) {
	m_totalTime += deltaTime;

	if (m_totalTime >= m_currentAnimation.speed()) {
		m_totalTime -= m_currentAnimation.speed();

		try {
			m_currentAnimation.nextFrame();
		} catch (EndAnimationException& exception) {
			if (m_currentAnimation.animationCycleFinish())
				playDefaultAnimation(side);
			else
				m_currentAnimation.resetAnimation();
		}

		updateCurrentTexture();
	}
}
sf::Texture& AnimationPlayer::getCurrentTexture() { return *m_currentTexture; }

void AnimationPlayer::playDefaultAnimation(const FacingSide& side) {
	switch (side) {
		case FacingSide::down: playAnimation(m_defaultAnimations.facingDown); break;
		case FacingSide::up: playAnimation(m_defaultAnimations.facingUp); break;
		case FacingSide::left: playAnimation(m_defaultAnimations.facingLeft); break;
		case FacingSide::right: playAnimation(m_defaultAnimations.facingRight); break;
	}

	updateCurrentTexture();
}