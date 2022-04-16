#ifndef I_LOGIC_HEADER_H
#define I_LOGIC_HEADER_H

#include <SFML/Graphics/Sprite.hpp>

template<typename T>
class ILogic {
public:
	virtual T* doLogic(const float deltaTime) = 0;
	virtual void initialize() = 0;

	void setSprite(sf::Sprite* sprite) { m_sprite = sprite; }
protected:
	T m_state;
	sf::Sprite* m_sprite;
};

#endif