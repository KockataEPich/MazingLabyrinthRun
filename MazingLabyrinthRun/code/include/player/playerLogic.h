#ifndef PLAYER_LOGIC_HEADER_H
#define PLAYER_LOGIC_HEADER_H

#include "../include/entityBase/logic/iLogic.h"
#include "../include/entityBase/logic/movable.h"
#include "../include/entityBase/component/borrowComponentMapObject.h"
#include "playerTextureEnum.h"
#include "playerState.h"

class PlayerLogic
    : public ILogic<PlayerState>
    , public BorrowComponentSpriteMapObject<PlayerComponents>
    , public Movable {
public:
	PlayerLogic(ComponentSpriteMap<PlayerComponents>*);
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