#ifndef PLAYER_VIEW_HEADER_H
#define PLAYER_VIEW_HEADER_H

#include "../include/animation/animationPlayer.h"
#include "../include/entityBase/component/borrowComponentMapObject.h"
#include "../include/entityBase/view/iView.h"
#include "playerState.h"
#include "playerTextureEnum.h"

class PlayerView
    : public IView<PlayerState>
    , public BorrowComponentSpriteMapObject<PlayerComponents> {
public:
	PlayerView(ComponentSpriteMap<PlayerComponents>*);
	void update(const PlayerState* state, const float deltaTime) override;

private:
	AnimationPlayer m_animate;
	void initialize() override;
};

#endif