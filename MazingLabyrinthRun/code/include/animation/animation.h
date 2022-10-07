#ifndef ANIMATION_HEADER_H
#define ANIMATION_HEADER_H

#include "../resource/resourceManager.h"
#include "../resource/textureEnum.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <exception>
#include <string>
#include <vector>

using Repeat = struct { int numberOfTimes; };
using AnimationSpeed = struct { float speed; };

class Animation {
public:
	Animation(Textures::ID texture_id, Repeat repeat, AnimationSpeed speed)
	    : m_repeat{repeat}
	    , m_speed{speed}
	    , m_texture_id{texture_id}
	    , m_texture{ResourceManager::getInstance()->getTexture(texture_id)} {
		m_x_axis_offset = m_texture->getSize().x / Textures::getNumberOfFrames(m_texture_id);
		m_current_rectange = {0, 0, m_x_axis_offset, (int) m_texture->getSize().y};
	};

	bool nextFrame();
	bool resetCycle();

	float speed() { return m_speed.speed; }

	sf::IntRect& get_current_rect() { return m_current_rectange; }
	sf::Texture* getTexture() { return m_texture; }
	Textures::ID& get_texture_id() { return m_texture_id; }

	void operator=(Animation& other) noexcept {
		m_x_axis_offset = other.m_x_axis_offset;
		m_texture_id = other.m_texture_id;
		m_repeat = other.m_repeat;
		m_speed = other.m_speed;
		m_texture = other.m_texture;

		m_current_rectange = sf::IntRect{0, 0, other.m_x_axis_offset, (int) m_texture->getSize().y};
	}
	friend bool operator==(const Animation& lhs, const Animation& rhs);

private:
	int m_x_axis_offset;
	sf::IntRect m_current_rectange;

	Textures::ID m_texture_id;
	sf::Texture* m_texture;
	Repeat m_repeat;
	AnimationSpeed m_speed;
};

#endif
