// ################## THIS FILE IS GENERATED ##################
#ifndef AI_SYSTEM_HEADER
#define AI_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>

#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/speed_component.h>
#include <generated/components/data_components/facing_side_component.h>
#include <generated/components/basic_components/ai_component.h>

class AISystem : public ProducerSystem {
public:
	AISystem() {
		m_signature
			.add_component<TransformComponent>()
			.add_component<SpeedComponent>()
			.add_component<FacingSideComponent>()
			.add_component<AIComponent>();
	}
	int const tick_frequency() override { return 5; }
	void update() override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<TransformComponent> transform;
			ComponentHandle<SpeedComponent> speed;
			ComponentHandle<FacingSideComponent> facing_side;
			m_parent_world->unpack(entity,
				transform,
				speed,
				facing_side);

			for_every_entity(entity,
				*transform,
				*speed,
				*facing_side);
		}
	}
private:

	void for_every_entity(
		Entity entity,
		TransformComponent& transform,
		SpeedComponent& speed,
		FacingSideComponent& facing_side);

};
#endif