#ifndef ANIMATION_HEADER_H
#define ANIMATION_HEADER_H

#include "../resource/resource_manager.h"
#include "../resource/texture_enum.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <exception>
#include <string>
#include <vector>

class Animation {
public:
	Animation(const Textures::ID& texture_id)
	    : m_speed{Textures::texture_id_to_texture_metadata.at(m_texture_id).default_speed}
	    , m_texture_id{texture_id}
	    , m_texture{ResourceManager::get_instance()->get_texture(texture_id)} {
		m_x_axis_offset =
		    m_texture->getSize().x / Textures::texture_id_to_texture_metadata.at(m_texture_id).number_of_frames;
		m_current_rectange = {0, 0, m_x_axis_offset, (int)m_texture->getSize().y};
	};

	bool next_frame();
	bool reset_cycle();

	float speed() { return m_speed; }

	sf::IntRect& get_current_rect() { return m_current_rectange; }
	sf::Texture* get_texture() { return m_texture; }
	Textures::ID& get_texture_id() { return m_texture_id; }

	void operator=(Animation& other) noexcept;
	friend bool operator==(const Animation& lhs, const Animation& rhs);

private:
	int m_x_axis_offset;
	sf::IntRect m_current_rectange;

	Textures::ID m_texture_id;
	sf::Texture* m_texture;
	int m_number_of_cycles;
	float m_speed;
};

#endif
