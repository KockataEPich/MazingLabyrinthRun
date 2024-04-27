#ifndef HEALTH_BAR_HEADER
#define HEALTH_BAR_HEADER

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <resource/resource_manager.h>

class HealthBar : public sf::Drawable {
public:
	HealthBar() = default;

	void initialize(const sf::Vector2f position,
					const sf::Vector2f size,
					int health,
					int max_health,
					bool display_hp = false) {
		m_display_hp = display_hp;
		m_current_health = health;
		m_max_health = max_health;

		m_health_bar.setPosition(position);
		m_health_bar.setSize(size);

		m_health_bar.setFillColor(sf::Color::Red);
		m_health_bar.setOutlineThickness(5);

		update_healt_bar_damage_offset();

		m_text.setFont(*ResourceManager::get_instance()->get_font("resources/fonts/Raleway-Black.ttf"));
		m_text.setString(std::to_string(m_current_health) + "/" + std::to_string(m_max_health));
		m_text.setCharacterSize(30);
		m_text.setOrigin(m_text.getLocalBounds().width * 0.5f, m_text.getLocalBounds().height * 0.5f);
		m_text.setPosition(m_health_bar.getPosition() + m_health_bar.getSize() * 0.5f);
	}

	void set_position(sf::Vector2f position) { 
		m_health_bar.setPosition(position);
		update_healt_bar_damage_offset();
		m_text.setPosition(m_health_bar.getPosition() + m_health_bar.getSize() * 0.5f);
	}

	void set_size(sf::Vector2f size) {
		m_health_bar.setSize(size);
		update_healt_bar_damage_offset();
		m_text.setPosition(m_health_bar.getPosition() + m_health_bar.getSize() * 0.5f);
	}
	void set_health(int health, int max_health) {
		m_current_health = health;
		m_max_health = max_health;
		update_healt_bar_damage_offset();
		m_text.setString(std::to_string(m_current_health) + "/" + std::to_string(m_max_health));
	}

private: 
	sf::RectangleShape m_health_bar;
	sf::RectangleShape m_health_bar_damage_offset;
	sf::Text m_text;

	int m_current_health;
	int m_max_health;

	bool m_display_hp;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(m_health_bar);
		target.draw(m_health_bar_damage_offset);
		if (m_display_hp) target.draw(m_text);
	}

	void update_healt_bar_damage_offset() {
		float health_percentage = (float) m_current_health / m_max_health;
		float left_of_rectangle = m_health_bar.getPosition().x + m_health_bar.getSize().x * health_percentage;
		float width_of_rectangle = m_health_bar.getSize().x - m_health_bar.getSize().x * health_percentage;

		m_health_bar_damage_offset.setSize({width_of_rectangle, m_health_bar.getSize().y});
		m_health_bar_damage_offset.setFillColor(sf::Color::Black);
		m_health_bar_damage_offset.setPosition({left_of_rectangle, m_health_bar.getPosition().y});
	}
};

#endif