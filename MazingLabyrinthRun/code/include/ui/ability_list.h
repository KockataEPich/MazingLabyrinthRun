#ifndef ABILITY_LIST_HEADER
#define ABILITY_LIST_HEADER

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <resource/resource_manager.h>
#include <time/time_manager.h>
#include <iomanip>

class AbilityList : public sf::Drawable {
public:
	AbilityList() = default;

	void initialize(sf::Vector2f size) { 
		m_ability_slot_1.setSize(size);
		m_ability_slot_1.setFillColor(sf::Color::Black);
		m_ability_slot_1.setOutlineThickness(5);


		cooldown_rectangle_1.setSize(size);
		cooldown_rectangle_1.setFillColor(sf::Color(128, 128, 128, 160));

		m_sprite_slot_1.setTexture(*ResourceManager::get_instance()->get_texture(Textures::ID::FIREBALL_1));
		m_sprite_slot_1.setScale({2.5,3});


		current_cooldown_as_seconds_1.setFont(
		    *ResourceManager::get_instance()->get_font("resources/fonts/Raleway-Black.ttf"));
		current_cooldown_as_seconds_1.setCharacterSize(25);
		current_cooldown_as_seconds_1.setOrigin(current_cooldown_as_seconds_1.getLocalBounds().width * 0.5f,
		                                        current_cooldown_as_seconds_1.getLocalBounds().height * 0.5f);
	}

	void set_position(sf::Vector2f position) { 
		m_ability_slot_1.setPosition(position);
		m_sprite_slot_1.setPosition(position);
		cooldown_rectangle_1.setPosition(position);
		current_cooldown_as_seconds_1.setPosition(cooldown_rectangle_1.getPosition());
	}

	void set_size(sf::Vector2f size) { m_ability_slot_1.setSize(size);}
	void update_cooldowns() { 
		if (float current_time = TimeManager::get_instance()->get_time_left("Fireball Attack"); current_time != 0) { 
			current_cooldown_as_seconds_1.setString(std::to_string(current_time).substr(0, 3));
			m_render_cooldown = true;
		} else {
			m_render_cooldown = false;
		}
	}

private: 
	sf::RectangleShape m_ability_slot_1;
	sf::Sprite m_sprite_slot_1;

	sf::RectangleShape cooldown_rectangle_1;
	sf::Text current_cooldown_as_seconds_1;

	bool m_render_cooldown = false;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(m_ability_slot_1);
		target.draw(m_sprite_slot_1);
		if (m_render_cooldown) { 
			target.draw(cooldown_rectangle_1);
			target.draw(current_cooldown_as_seconds_1);
		}
	}
};

#endif