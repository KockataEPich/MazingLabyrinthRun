#ifndef ANIMATION_HEADER_H
#define ANIMATION_HEADER_H

#include "../resource/resourceManager.h"
#include "../resource/textureEnum.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <exception>
#include <string>
#include <vector>

using Repeat = struct { int number_of_times; };
using AnimationSpeed = struct { float speed; };

class Animation {
public:
	Animation(const Textures::ID& texture_id)
	    : m_repeat{Textures::texture_id_to_texture_metadata.at(m_texture_id).default_repeats}
	    , m_speed{Textures::texture_id_to_texture_metadata.at(m_texture_id).default_speed}
	    , m_texture_id{texture_id}
	    , m_texture{ResourceManager::getInstance()->getTexture(texture_id)} {
		m_x_axis_offset =
		    m_texture->getSize().x / Textures::texture_id_to_texture_metadata.at(m_texture_id).number_of_frames;
		m_current_rectange = {0, 0, m_x_axis_offset, (int)m_texture->getSize().y};
	};

	bool next_frame();
	bool reset_cycle();

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

		m_current_rectange = sf::IntRect{0, 0, other.m_x_axis_offset, (int)m_texture->getSize().y};
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
