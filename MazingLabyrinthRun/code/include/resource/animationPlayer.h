#ifndef ANIMATION_PLAYER_HEADER_H
#define ANIMATION_PLAYER_HEADER_H

#include "../world/iMovingObject.h"
#include "animation.h"

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

template<typename T>
class AnimationPlayer {
public:
	template<typename T>
	struct DefaultAnimations {
		Animation<T> facingRight;
		Animation<T> facingLeft;
		Animation<T> facingUp;
		Animation<T> facingDown;
	};

	AnimationPlayer(std::unordered_map<T, sf::Texture>& textures, DefaultAnimations<T>& defaultAnimations);

	sf::Texture& getCurrentTexture();
	void playAnimation(Animation<T>& animation);
	void update(FacingSide side, float deltaTime);
	void playDefaultAnimation(FacingSide side);

private:
	float m_totalTime = 0.0f;
	DefaultAnimations<T> m_defaultAnimations;
	Animation<T> m_currentAnimation;
	std::unordered_map<T, sf::Texture>* m_textures;
	sf::Texture* m_currentTexture;

	void updateCurrentTexture() { m_currentTexture = &m_textures->at(m_currentAnimation.currentFrame()); }
};

template<typename T>
AnimationPlayer<T>::AnimationPlayer(std::unordered_map<T, sf::Texture>& textures,
                                    DefaultAnimations<T>& defaultAnimations)
    : m_defaultAnimations{defaultAnimations} {
	m_textures = &textures;
	playAnimation(m_defaultAnimations.facingRight);
}

template<typename T>
void AnimationPlayer<T>::playAnimation(Animation<T>& animation) {
	if (m_currentAnimation == animation) return;
	m_currentAnimation = animation;
	updateCurrentTexture();
}

template<typename T>
void AnimationPlayer<T>::update(FacingSide side, float deltaTime) {
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

template<typename T>
sf::Texture& AnimationPlayer<T>::getCurrentTexture() {
	return *m_currentTexture;
}

template<typename T>
void AnimationPlayer<T>::playDefaultAnimation(FacingSide side) {
	switch (side) {
		case FacingSide::down: playAnimation(m_defaultAnimations.facingDown); break;
		case FacingSide::up: playAnimation(m_defaultAnimations.facingUp); break;
		case FacingSide::left: playAnimation(m_defaultAnimations.facingLeft); break;
		case FacingSide::right: playAnimation(m_defaultAnimations.facingRight); break;
	}

	updateCurrentTexture();
}

#endif
