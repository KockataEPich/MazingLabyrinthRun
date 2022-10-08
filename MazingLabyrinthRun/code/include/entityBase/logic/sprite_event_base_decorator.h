#ifndef SPRITE_EVENT_DECORATOR_BASE_HEADER
#define SPRITE_EVENT_DECORATOR_BASE_HEADER

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