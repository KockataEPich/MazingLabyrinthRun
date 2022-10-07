#include "../include/player/playerView.h"

#include "../include/player/playerTextureEnum.h"

Animation run_right{Textures::ID::NORRIS_RUN_RIGHT, 16, Repeat{-1}, AnimationSpeed{0.2}};
Animation run_left{Textures::ID::NORRIS_RUN_LEFT, 16, Repeat{-1}, AnimationSpeed{0.2}};
Animation run_up{Textures::ID::NORRIS_RUN_UP, 16, Repeat{-1}, AnimationSpeed{0.2}};
Animation run_down{Textures::ID::NORRIS_RUN_DOWN, 16, Repeat{-1}, AnimationSpeed{0.2}};

PlayerView::PlayerView()
    : m_animate{
          {Animation{Textures::ID::NORRIS_NAKED_WALK_RIGHT_1, 16, Repeat{-1}, AnimationSpeed{0.2}},
           Animation{Textures::ID::NORRIS_NAKED_WALK_LEFT_1, 16, Repeat{-1}, AnimationSpeed{0.2}},
           Animation{Textures::ID::NORRIS_NAKED_WALK_UP_1, 16, Repeat{-1}, AnimationSpeed{0.2}},
           Animation{Textures::ID::NORRIS_NAKED_WALK_DOWN_1, 16, Repeat{-1}, AnimationSpeed{0.2}}},
      } {}

void PlayerView::initialize() {
	m_sprite->setTexture(m_animate.getCurrentTexture());
	m_sprite->setTextureRect(m_animate.get_current_rect());
}

void PlayerView::update(const PlayerState* state, const float deltaTime) {
	if (state->currentAnimation == PlayerAnimation::run) {
		if (state->side == FacingSide::right) m_animate.playAnimation(run_right);
		if (state->side == FacingSide::left) m_animate.playAnimation(run_left);
		if (state->side == FacingSide::up) m_animate.playAnimation(run_up);
		if (state->side == FacingSide::down) m_animate.playAnimation(run_down);
	} else
		m_animate.playDefaultAnimation(state->side);

	m_animate.update(state->side, deltaTime);
	m_sprite->setTexture(m_animate.getCurrentTexture());
	m_sprite->setTextureRect(m_animate.get_current_rect());
}