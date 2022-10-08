#ifndef MOVING_SPRITE_EVENT_DECORATOR_HEADER_H
#define MOVING_SPRITE_EVENT_DECORATOR_HEADER_H

#include "../action.h"
#include "movable_state.h"

class MoveAction : public Action {
public:
	MoveAction(MovableState* state, sf::Sprite* sprite) : Action(sprite), m_state{state} {};
	virtual void apply() = 0;

protected:
	MovableState* m_state;
};

class MoveRight : public MoveAction {
public:
	MoveRight(MovableState* state, sf::Sprite* sprite) : MoveAction(state, sprite){};
	void apply() override {
		m_sprite->setPosition(m_sprite->getPosition().x + (m_state->speed * m_state->delta_time),
		                      m_sprite->getPosition().y);
		m_state->side = FacingSide::right;
	};
};

class MoveLeft : public MoveAction {
public:
	MoveLeft(MovableState* state, sf::Sprite* sprite) : MoveAction(state, sprite){};
	void apply() override {
		m_sprite->setPosition(m_sprite->getPosition().x - (m_state->speed * m_state->delta_time), m_sprite->getPosition().y);
		m_state->side = FacingSide::left;
	};
};

class MoveUp : public MoveAction {
public:
	MoveUp(MovableState* state, sf::Sprite* sprite) : MoveAction(state, sprite){};
	void apply() override {
		m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y - (m_state->speed * m_state->delta_time));
		m_state->side = FacingSide::up;
	};
};

class MoveDown : public MoveAction {
public:
	MoveDown(MovableState* state, sf::Sprite* sprite) : MoveAction(state, sprite){};
	void apply() override {
		m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + (m_state->speed * m_state->delta_time));
		m_state->side = FacingSide::down;
	};
};

#endif