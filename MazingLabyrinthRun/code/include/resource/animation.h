#ifndef ANIMATION_HEADER_H
#define ANIMATION_HEADER_H

#include "textureHolder.h"
template <typename T>
class Animation {
public:
	Animation(TextureHolder<T>& textureHolder, T initial_frame);
	sf::Texture& getCurrentTexture();
	void playAnimation(float speed, const std::vector<T>& animationFrames);
	void update(float deltaTime);
	void playDefaultAnimation();

private:
	int m_textureIndex = 0;
	float m_totalTime = 0.0f;
	float m_animationSpeed = 0.3f;

	std::vector<T> m_currentAnimation;
	TextureHolder<T>* m_textureHolder;
	sf::Texture* m_currentTexture;
};

template <typename T>
Animation<T>::Animation(TextureHolder<T>& textureHolder, T initial_frame) {
	m_textureHolder = &textureHolder;
	m_currentTexture = &(m_textureHolder->getTexture(initial_frame));
}

template <typename T>
void Animation<T>::playAnimation(float speed, const std::vector<T>& animationFrames) {
	if(m_currentAnimation == animationFrames)
		return;

	m_animationSpeed = speed;
	m_currentAnimation = animationFrames;

	m_textureIndex = 0;
	m_currentTexture = &(m_textureHolder->getTexture(animationFrames.at(m_textureIndex)));
}

template <typename T>
void Animation<T>::update(float deltaTime) {
	if(m_currentAnimation.size() == 0)
		return;

	m_totalTime += deltaTime;

	if(m_totalTime >= m_animationSpeed) {
		m_totalTime -= m_animationSpeed;
		m_textureIndex++;

		if(m_textureIndex == m_currentAnimation.size()) {
			m_textureIndex = 0;
		}

		m_currentTexture = &m_textureHolder->getTexture(m_currentAnimation.at(m_textureIndex));
	}
}

template <typename T>
sf::Texture& Animation<T>::getCurrentTexture() {
	return *m_currentTexture;
}

template <typename T>
void Animation<T>::playDefaultAnimation() {
	if(m_currentAnimation.size() == 0)
		return;
	m_currentTexture = &m_textureHolder->getTexture(m_currentAnimation.at(0));
}

#endif
