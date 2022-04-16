#ifndef PLAYER_LOGIC_HEADER_H
#define PLAYER_LOGIC_HEADER_H

#include "../entityBase/iLogic.h"
#include "../entityBase/movable.h"
#include "playerState.h"

class PlayerLogic
    : public ILogic<PlayerState>
    , public Movable {
public:
	PlayerLogic();
	PlayerState* doLogic(const float deltaTime) override;
	void move(const float deltaTime) override;

private:
	void initialize() override;

	void moveRight(const float deltaTime);
	void moveLeft(const float deltaTime);
	void moveUp(const float deltaTime);
	void moveDown(const float deltaTime);
};

#endif