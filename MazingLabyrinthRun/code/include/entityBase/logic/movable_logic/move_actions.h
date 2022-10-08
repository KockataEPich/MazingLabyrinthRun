#ifndef MOVING_RUN_ACTION_HEADER_H
#define MOVING_RUN_ACTION_HEADER_H

#include "../action.h"
#include "movable_state.h"

class RunAction : public ActionUsingState<MovableState> {
public:
	RunAction(sf::Sprite* sprite, MovableState* state) : ActionUsingState<MovableState>(sprite, state) {};
	void after_applying() override {m_state->action_type = ActionType::run;}
};

class RunRight : public RunAction {
public:
	RunRight(sf::Sprite* sprite, MovableState* state) : RunAction(sprite, state){};
	void apply_action() override {
		m_sprite->setPosition(m_sprite->getPosition().x + (m_state->speed * m_state->delta_time),
		                      m_sprite->getPosition().y);
		m_state->side = FacingSide::right;
	};
};

class RunLeft : public RunAction {
public:
	RunLeft(sf::Sprite* sprite, MovableState* state) : RunAction(sprite, state){};
	void apply_action() override {
		m_sprite->setPosition(m_sprite->getPosition().x - (m_state->speed * m_state->delta_time), m_sprite->getPosition().y);
		m_state->side = FacingSide::left;
	};
};

class RunUp : public RunAction {
public:
	RunUp(sf::Sprite* sprite, MovableState* state) : RunAction(sprite, state){};
	void apply_action() override {
		m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y - (m_state->speed * m_state->delta_time));
		m_state->side = FacingSide::up;
	};
};

class RunDown : public RunAction {
public:
	RunDown(sf::Sprite* sprite, MovableState* state) : RunAction(sprite, state){};
	void apply_action() override {
		m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + (m_state->speed * m_state->delta_time));
		m_state->side = FacingSide::down;
	};
};

#endif