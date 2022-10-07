#ifndef ANIMATION_HEADER_H
#	define ANIMATION_HEADER_H

#	include "../resource/textureEnum.h"
#	include "../resource/resourceManager.h"
#	include <SFML/Graphics/Rect.hpp>
#	include <SFML/Graphics/Texture.hpp>
#	include <exception>
#	include <string>
#	include <vector>

using Repeat = struct { int numberOfTimes; };
using AnimationSpeed = struct { float speed; };

class Animation {
public:
	Animation(Textures::ID texture_id, int x_axis_offset, Repeat repeat, AnimationSpeed speed)
	    : m_x_axis_offset{x_axis_offset}
	    , m_repeat{repeat}
	    , m_speed{speed}
	    , m_texture_id{texture_id}
	    , m_texture{*ResourceManager::getInstance()->getTexture(texture_id)} {};

	bool nextFrame();
	bool resetCycle();

	float speed() { return m_speed.speed; }

	sf::IntRect& get_current_rect() { return m_current_rectange; }
	sf::Texture& getTexture() { return m_texture; }

	void operator=(Animation& other) noexcept {
		m_x_axis_offset = other.m_x_axis_offset;
		m_texture_id = other.m_texture_id;
		m_repeat = other.m_repeat;
		m_speed = other.m_speed;
		m_texture = other.m_texture;

		m_current_rectange = sf::IntRect{0, 0, 16, 16};
	}
	friend bool operator==(const Animation& lhs, const Animation& rhs);

private:
	int m_x_axis_offset;
	sf::IntRect m_current_rectange{0, 0, 16, 16};

	Textures::ID m_texture_id;
	sf::Texture& m_texture;
	Repeat m_repeat;
	AnimationSpeed m_speed;
};

#endif

/*

void AnimationPlayer::update(const FacingSide& side, float deltaTime) {
    if (!with_style) {
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
}*/
