#ifndef PLAYER_VIEW_HEADER_H
#define PLAYER_VIEW_HEADER_H

#include "../entityBase/iView.h"
#include "../animation/animationPlayer.h"
#include "playerState.h"

class PlayerView : public IView<PlayerState> {
public:
	PlayerView();
	void update(const PlayerState* state, const float deltaTime) override;

private:
	AnimationPlayer m_animate;
	void initialize() override;
};
	
#endif