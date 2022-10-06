#ifndef ANIMATION_PLAYER_HEADER_H
#define ANIMATION_PLAYER_HEADER_H

#include "../include/resource/resourceManager.h"
#include "../include/attribute/facingSide.h"
#include "animation.h"

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class AnimationPlayer {
public:
	struct DefaultAnimations {
		Animation facingRight;
		Animation facingLeft;
		Animation facingUp;
		Animation facingDown;
	};

	AnimationPlayer(DefaultAnimations& defaultAnimations);

	sf::Texture& getCurrentTexture();
	void playAnimation(Animation& animation);
	void playAnimationWithStyle(Animation& animation);
	void update(const FacingSide& side, float deltaTime);
	void playDefaultAnimation(const FacingSide& side);

private:
	float m_totalTime = 0.0f;
	DefaultAnimations m_defaultAnimations;
	bool with_style = false;
	Animation m_currentAnimation;
	sf::Texture* m_currentTexture;

	void updateCurrentTexture() {
		m_currentTexture = ResourceManager::getInstance()->getTexture(m_currentAnimation.currentFrame());
	}
};

#endif
