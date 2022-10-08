#ifndef PLAYER_LOGIC_HEADER_H
#define PLAYER_LOGIC_HEADER_H

#include "../include/entityBase/logic/action.h"
#include "../include/entityBase/logic/iLogic.h"
#include "player_state.h"

#include <memory>

class PlayerLogic : public ILogic<PlayerState> {
public:
	PlayerLogic();
	PlayerState* doLogic(const float deltaTime) override;

private:
	void initialize() override;
	void fill_actions_from_play_input(std::vector<std::unique_ptr<Action>>& actions);
};

#endif