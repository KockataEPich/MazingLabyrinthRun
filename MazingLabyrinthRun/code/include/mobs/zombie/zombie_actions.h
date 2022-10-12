#ifndef ZOMBIE_ACTIONS_HEADER_H
#define ZOMBIE_ACTIONS_HEADER_H
#include "../include/entityBase/logic/movable_logic/move_actions.h"
#include <functional>
#include <memory>

class ZombieAttackEvent : public EventUsingState<ZombieState> {
public:
	ZombieAttackEvent(sf::Sprite* sprite, ZombieState* state) : EventUsingState<ZombieState>(sprite, state){};
	void event() override { m_state->action_type = ActionType::attack; }
};



#endif