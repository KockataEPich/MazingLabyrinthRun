#ifndef SPRITE_ACTION_HEADER
#define SPRITE_ACTION_HEADER

#include <SFML/Graphics/Sprite.hpp>
class Action {
public:
	Action(sf::Sprite* sprite) : m_sprite{sprite}{}
	virtual void apply() = 0;
	bool is_finished() {return m_finished;}
protected:
	sf::Sprite* m_sprite;
	bool m_finished = true;
};

#endif