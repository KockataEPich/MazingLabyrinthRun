#ifndef PLAYER_HEADER_H
#define PLAYER_HEADER_H

#include "../include/entityBase/complexWorldObject/activeObject.h"
#include "playerLogic.h"
#include "playerView.h"

#include <SFML/Graphics/Texture.hpp>

class Player : public ActiveObject<PlayerState> {
public:
	Player() : ActiveObject(std::move(std::make_unique<PlayerLogic>()), std::move(std::make_unique<PlayerView>())){};

private:
};

#endif