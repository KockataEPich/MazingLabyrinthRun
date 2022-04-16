#include "../include/player/playerView.h"

#include "../include/player/playerTextureEnum.h"

Animation dRightAnimation("Default Right Animation", defaultRightAnimation, Repeat{-1}, AnimationSpeed{0.3f});
Animation dLeftAnimation("Default Left Animation", defaultLeftAnimation, Repeat{-1}, AnimationSpeed{0.3f});
Animation dUpAnimation("Default Up Animation", defaultUpAnimation, Repeat{-1}, AnimationSpeed{0.3f});
Animation dDownAnimation("Default Down Animation", defaultDownAnimation, Repeat{-1}, AnimationSpeed{0.3f});

PlayerView::PlayerView()
    : m_animate{AnimationPlayer(
          AnimationPlayer::DefaultAnimations{dRightAnimation, dLeftAnimation, dUpAnimation, dDownAnimation})} {}

void PlayerView::initialize() { 
	m_sprite->setTexture(m_animate.getCurrentTexture()); 
}

void PlayerView::update(const PlayerState* state, const float deltaTime) {
	if (state->currentAnimation == PlayerAnimation::run) {
		if (state->side == FacingSide::right)
			m_animate.playAnimation(
			    Animation("Run Right Animation", runRightAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
		if (state->side == FacingSide::left) {
			m_animate.playAnimation(
			    Animation("Run Left Animation", runLeftAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
		}
		if (state->side == FacingSide::up)
			m_animate.playAnimation(
			    Animation("Run Up Animation", runUpAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
		if (state->side == FacingSide::down)
			m_animate.playAnimation(
			    Animation("Run down Animation", runDownAnimation, Repeat{-1}, AnimationSpeed{0.2f}));
	} else {
		m_animate.playDefaultAnimation(state->side);
	}

	m_animate.update(state->side, deltaTime);
	m_sprite->setTexture(m_animate.getCurrentTexture());
}

//