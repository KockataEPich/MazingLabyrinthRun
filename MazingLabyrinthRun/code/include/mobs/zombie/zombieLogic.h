#ifndef ZOMBIE_LOGIC_HEADER_H
#define ZOMBIE_LOGIC_HEADER_H

#include "../include/entityBase/complexWorldObject/activeObject.h"
#include "zombieView.h"

#include <SFML/Graphics/Texture.hpp>

class ZombieLogic : public ILogic<ZombieState> {
public:
	ZombieLogic();
	ZombieState* doLogic(const float deltaTime) override;

private:
	void initialize() override;
	void fill_actions_from_play_input(std::vector<std::unique_ptr<Event>>& actions);
};

#endif