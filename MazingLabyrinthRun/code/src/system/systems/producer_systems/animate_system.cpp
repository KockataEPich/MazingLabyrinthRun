#include <generated/systems/producer_systems/animate_system.h>
#include <generated/components/basic_components/initiate_action_component.h>
void AnimateSystem::for_every_entity(
	Entity entity,
	ActionTypeComponent& action_type,
	SkinComponent& skin,
	FacingSideComponent& facing_side,
	AnimationPlayerComponent& animation_player,
	TransformComponent& transform,
	SpriteComponent& sprite){ 

	auto texture_id = get_id_of_rotating_texture(skin.skin, action_type.action_type);
	if (texture_id != animation_player.animation_player.get_current_animation().get_texture_id()) {
		animation_player.animation_player.play_animation(Animation(texture_id));
		sprite.sprite.setTexture(animation_player.animation_player.get_current_texture());

		if (facing_side.side == FacingSide::right)
			transform.scale.x = -std::abs(transform.scale.x);
		else
			transform.scale.x = std::abs(transform.scale.x);
	}

	animation_player.animation_player.update(facing_side.side);
	sprite.sprite.setTextureRect(animation_player.animation_player.get_current_rect());
	transform.size = {(float)sprite.sprite.getTextureRect().width,
	                     (float)sprite.sprite.getTextureRect().height};

	if (animation_player.animation_player.is_action_frame())
		m_parent_world->add_event_component(entity, std::make_unique<InitiateActionComponent>());
}

