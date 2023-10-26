// ################## THIS FILE IS GENERATED ##################
#ifndef MOVE_SYSTEM_HEADER
#define MOVE_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>

#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/speed_component.h>
#include <generated/components/data_components/target_for_direction_component.h>
#include <generated/components/basic_components/move_component.h>

class MoveSystem : public ReactSystem {
public:
	MoveSystem() {
		m_signature
			.add_component<TransformComponent>()
			.add_component<SpeedComponent>()
			.add_component<TargetForDirectionComponent>()
			.add_component<MoveComponent>();
	}
	void react(const Entity& entity) override {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<TargetForDirectionComponent> target_for_direction;
		m_parent_world->unpack(entity,
			transform,
			speed,
			target_for_direction);

		react_on_entity(entity,
			*transform,
			*speed,
			*target_for_direction);
	}
private:

	void react_on_entity(
		Entity entity,
		TransformComponent& transform,
		SpeedComponent& speed,
		TargetForDirectionComponent& target_for_direction);

};
#endif