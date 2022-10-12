#ifndef ZOMBIE_HEADER_H
#define ZOMBIE_HEADER_H

#include "../include/entityBase/complexWorldObject/activeObject.h"
#include "../include/entityBase/logic/event.h"
#include "../include/entityBase/logic/iLogic.h"

#include "zombieLogic.h"
#include "zombieView.h"
#include "zombie_state.h"

#include <SFML/Graphics/Texture.hpp>
#include <memory>

class Zombie : public ActiveObject<ZombieState> {
public:
	Zombie() : ActiveObject(std::move(std::make_unique<ZombieLogic>()), std::move(std::make_unique<ZombieView>())){};

private:
};

#endif