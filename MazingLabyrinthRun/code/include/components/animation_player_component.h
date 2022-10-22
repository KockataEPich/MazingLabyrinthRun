#ifndef ANIMATION_PLAYER_COMPONENT_HEADER
#define ANIMATION_PLAYER_COMPONENT_HEADER

#include "../animation/animation_player.h"

struct AnimationPlayerComponent : public Component<AnimationPlayerComponent> {
	explicit AnimationPlayerComponent(DefaultAnimations&& default_animations)
	    : m_animation_player{std::move(default_animations)} {};
	m_animation_player;
};

/*AnimatedView(Skin&& start_skin, DefaultAnimations&& default_animations)
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
};*/

#endif