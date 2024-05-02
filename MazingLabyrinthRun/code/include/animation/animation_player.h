#ifndef ANIMATION_PLAYER_HEADER_H
#define ANIMATION_PLAYER_HEADER_H

#include "../include/attribute/facing_side.h"
#include "../include/resource/skins.h"
#include "animation.h"

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class AnimationPlayer {
public:
	AnimationPlayer() : m_current_animation(Textures::ID::DEFAULT_PLACEHOLDER_TEXTURE){};

	void update(const FacingSide& side);

	void set_skin(Skin skin) { m_skin = skin; }
	void play_animation(Animation&& animation) { m_current_animation = animation; }

	Animation& get_current_animation() { return m_current_animation; };
	sf::IntRect& get_current_rect(){ return m_current_animation.get_current_rect(); }
	sf::Texture& get_current_texture() { return *m_current_animation.get_texture(); };

	Skin& get_skin() { return m_skin; };
	void flash_white();

	bool is_action_frame() { return m_current_animation.is_action_frame(); }
	bool is_flashed() { return m_flash_white; }
	
private:
	float m_total_time = 0.0f;
	Skin m_skin = Skin::DEFAULT_PLACEHOLDER_SKIN;
	Animation m_current_animation;
	bool m_flash_white = false;

	void remove_flashing_if_finished();
};

#endif
