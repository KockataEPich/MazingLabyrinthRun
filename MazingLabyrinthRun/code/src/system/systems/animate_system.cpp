#include "../include/system/systems/animate_system.h"
#include "../include/component_base/component_handle.h"

void Animate::update() {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<SpriteComponent> sprite;
		ComponentHandle<FacingSideComponent> side;
		ComponentHandle<AnimationPlayerComponent> animation_player;
		ComponentHandle<ActionTypeComponent> action_type;
		ComponentHandle<SkinComponent> skin;
		ComponentHandle<TransformComponent> transform;

		m_parent_world->unpack(entity, sprite, side, animation_player, skin, action_type, transform);

		auto texture_id = get_id_of_rotating_texture(skin->m_skin, action_type->m_action_type, side->m_side);
		if (texture_id != animation_player->m_animation_player.get_current_animation().get_texture_id()) {
			animation_player->m_animation_player.play_animation(Animation(texture_id));
			sprite->m_sprite.setTexture(animation_player->m_animation_player.get_current_texture());
		}

		animation_player->m_animation_player.update(side->m_side);
		sprite->m_sprite.setTextureRect(animation_player->m_animation_player.get_current_rect());
	}
}