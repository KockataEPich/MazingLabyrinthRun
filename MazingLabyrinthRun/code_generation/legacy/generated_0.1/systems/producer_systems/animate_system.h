// ################## THIS FILE IS GENERATED ##################
#ifndef ANIMATE_SYSTEM_HEADER
#define ANIMATE_SYSTEM_HEADER

#include <world/world.h>

#include <generated/components/data_components/action_type_component.h>
#include <generated/components/data_components/skin_component.h>
#include <generated/components/data_components/facing_side_component.h>
#include <generated/components/data_components/animation_player_component.h>
#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/sprite_component.h>

class AnimateSystem : public ProducerSystem {
public:
	AnimateSystem() {
		m_signature
			.add_component<ActionTypeComponent>()
			.add_component<SkinComponent>()
			.add_component<FacingSideComponent>()
			.add_component<AnimationPlayerComponent>()
			.add_component<TransformComponent>()
			.add_component<SpriteComponent>();
	}
	void update() override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<ActionTypeComponent> action_type;
			ComponentHandle<SkinComponent> skin;
			ComponentHandle<FacingSideComponent> facing_side;
			ComponentHandle<AnimationPlayerComponent> animation_player;
			ComponentHandle<TransformComponent> transform;
			ComponentHandle<SpriteComponent> sprite;
			m_parent_world->unpack(entity,
				action_type,
				skin,
				facing_side,
				animation_player,
				transform,
				sprite);

			for_every_entry(Entity entity,
				*action_type,
				*skin,
				*facing_side,
				*animation_player,
				*transform,
				*sprite);
		}
	}
private:

	void for_every_entity(Entity entity,
		ActionTypeComponent& action_type,
		SkinComponent& skin,
		FacingSideComponent& facing_side,
		AnimationPlayerComponent& animation_player,
		TransformComponent& transform,
		SpriteComponent& sprite);

};
#endif