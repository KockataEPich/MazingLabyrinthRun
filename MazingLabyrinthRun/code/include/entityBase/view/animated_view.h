#ifndef ANIMATED_VIEW_HEADER_H
#define ANIMATED_VIEW_HEADER_H

#include "animation/animationPlayer.h"
#include "entityBase/complexWorldObject/active_object_state.h"
#include "../logic/movable_logic/movable_state.h"
#include "iView.h"

template <typename T, std::enable_if_t<std::is_base_of_v<MovableState, T>, bool> = true>
class AnimatedView : public IView<T> {
public:
	AnimatedView(Skin&& start_skin, DefaultAnimations&& default_animations)
	: IView<T>(std::move(start_skin))
	    , m_animate(std::move(default_animations)){};

	void update(const T* state, const float deltaTime) override {
		auto texture_id = get_id_of_rotating_texture(m_skin, state->action_type, state->side);
		if (texture_id != m_animate.getCurrentAnimation().get_texture_id()) {
			m_animate.playAnimation(Animation(texture_id));
			m_sprite->setTexture(m_animate.getCurrentTexture());
		}
		m_animate.update(state->side, deltaTime);
		m_sprite->setTextureRect(m_animate.get_current_rect());
	};
	void initialize() {
		m_sprite->setTexture(m_animate.getCurrentTexture());
		m_sprite->setTextureRect(m_animate.get_current_rect());
	};

protected:
	AnimationPlayer m_animate;
};

#endif