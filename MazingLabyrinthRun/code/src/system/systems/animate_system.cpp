#include "../include/system/systems/animate_system.h"
#include "../include/component_base/component_handle.h"

void Animate::update(float dt) {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<SpriteComponent> sprite;
		ComponentHandle<FacingSideComponent> side;
		ComponentHandle<AnimationPlayerComponent> animation_player;
		ComponentHandle<ActionTypeComponent> action_type;
		ComponentHandle<SkinComponent> skin;

		m_parent_world->unpack(entity, sprite, side, animation_player, skin, action_type);

		auto texture_id = get_id_of_rotating_texture(skin->m_skin, action_type->m_action_type, side->m_side);
		if (texture_id != animation_player->m_animation_player.get_current_animation().get_texture_id()) {
			animation_player->m_animation_player.play_animation(Animation(texture_id));
			sprite->m_sprite.setTexture(animation_player->m_animation_player.get_current_texture());
		}
		animation_player->m_animation_player.update(side->m_side, dt);
		sprite->m_sprite.setTextureRect(animation_player->m_animation_player.get_current_rect());
	}
}

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