#ifndef MOVING_RUN_ACTION_HEADER_H
#define MOVING_RUN_ACTION_HEADER_H

#include "../event.h"
#include "movable_state.h"

class RunEvent : public EventUsingState<MovableState> {
public:
	RunEvent(sf::Sprite* sprite, MovableState* state) : EventUsingState<MovableState>(sprite, state) {};
	void after_event() override {m_state->action_type = ActionType::run;}
};

class RunRight : public RunEvent {
public:
	RunRight(sf::Sprite* sprite, MovableState* state) : RunEvent(sprite, state){};
	void event() override {
		m_sprite->setPosition(m_sprite->getPosition().x + (m_state->speed * m_state->delta_time),
		                      m_sprite->getPosition().y);
		m_state->side = FacingSide::right;
	};
};

class RunLeft : public RunEvent {
public:
	RunLeft(sf::Sprite* sprite, MovableState* state) : RunEvent(sprite, state){};
	void event() override {
		m_sprite->setPosition(m_sprite->getPosition().x - (m_state->speed * m_state->delta_time), m_sprite->getPosition().y);
		m_state->side = FacingSide::left;
	};
};

class RunUp : public RunEvent {
public:
	RunUp(sf::Sprite* sprite, MovableState* state) : RunEvent(sprite, state){};
	void event() override {
		m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y - (m_state->speed * m_state->delta_time));
		m_state->side = FacingSide::up;
	};
};

class RunDown : public RunEvent {
public:
	RunDown(sf::Sprite* sprite, MovableState* state) : RunEvent(sprite, state){};
	void event() override {
		m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + (m_state->speed * m_state->delta_time));
		m_state->side = FacingSide::down;
	};
};

#endif