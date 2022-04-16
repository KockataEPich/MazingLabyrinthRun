#ifndef I_VIEW_HEADER_H
#define I_VIEW_HEADER_H

#include <SFML/Graphics/Sprite.hpp>

template<typename T>
class IView {
public:
	virtual void update(const T* state, const float deltaTime) = 0;
	virtual void initialize() = 0;

	void setSprite(sf::Sprite* sprite) { m_sprite = sprite; }

protected:
	sf::Sprite* m_sprite;
};

#endif