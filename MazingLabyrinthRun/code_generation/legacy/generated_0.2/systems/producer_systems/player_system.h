// ################## THIS FILE IS GENERATED ##################
#ifndef PLAYER_SYSTEM_HEADER
#define PLAYER_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>

#include <generated/components/data_components/action_type_component.h>
#include <generated/components/data_components/facing_side_component.h>
#include <generated/components/data_components/target_for_direction_component.h>
#include <generated/components/basic_components/player_component.h>
#include <generated/components/data_components/speed_component.h>
#include <generated/components/data_components/transform_component.h>

class PlayerSystem : public ProducerSystem {
public:
	PlayerSystem() {
		m_signature
			.add_component<ActionTypeComponent>()
			.add_component<FacingSideComponent>()
			.add_component<TargetForDirectionComponent>()
			.add_component<PlayerComponent>()
			.add_component<SpeedComponent>()
			.add_component<TransformComponent>();
	}
	void init() override { m_registered_entities.reserve(1); }  // Only one player
	void update() override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<ActionTypeComponent> action_type;
			ComponentHandle<FacingSideComponent> facing_side;
			ComponentHandle<TargetForDirectionComponent> target_for_direction;
			ComponentHandle<SpeedComponent> speed;
			ComponentHandle<TransformComponent> transform;
			m_parent_world->unpack(entity,
				action_type,
				facing_side,
				target_for_direction,
				speed,
				transform);

			for_every_entity(entity,
				*action_type,
				*facing_side,
				*target_for_direction,
				*speed,
				*transform);
		}
	}
private:

	void for_every_entity(
		Entity entity,
		ActionTypeComponent& action_type,
		FacingSideComponent& facing_side,
		TargetForDirectionComponent& target_for_direction,
		SpeedComponent& speed,
		TransformComponent& transform);

};
#endif