#include "../include/player/playerView.h"

PlayerView::PlayerView()
    : IView<PlayerState>(Skin::MAIN_CHARACTER_START_SKIN)
    , m_animate{{Animation(Textures::ID::NORRIS_NAKED_DEF_RIGHT_1, Repeat{-1}, AnimationSpeed{0.2}),
                 Animation(Textures::ID::NORRIS_NAKED_DEF_LEFT_1, Repeat{-1}, AnimationSpeed{0.2}),
                 Animation(Textures::ID::NORRIS_NAKED_DEF_UP_1, Repeat{-1}, AnimationSpeed{0.2}),
                 Animation(Textures::ID::NORRIS_NAKED_DEF_DOWN_1, Repeat{-1}, AnimationSpeed{0.2})}} {}

void PlayerView::initialize() {
	m_sprite->setTexture(m_animate.getCurrentTexture());
	m_sprite->setTextureRect(m_animate.get_current_rect());
}

void PlayerView::update(const PlayerState* state, const float deltaTime) {
	auto texture_id = get_id_of_rotating_texture(m_skin, state->current_animation, state->side);
	if (texture_id != m_animate.getCurrentAnimation().get_texture_id()) {
		if (state->current_animation == AnimationType::MAIN_CHARACTER_DEFAULT_JUMP)
			m_animate.playAnimation(Animation(texture_id, Repeat{1}, AnimationSpeed{0.1}));
		else
			m_animate.playAnimation(Animation(texture_id, Repeat{-1}, AnimationSpeed{0.2}));
		m_sprite->setTexture(m_animate.getCurrentTexture());
	}
	m_animate.update(state->side, deltaTime);
	m_sprite->setTextureRect(m_animate.get_current_rect());
}
