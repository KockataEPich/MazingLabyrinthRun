// ################## THIS FILE IS GENERATED ##################
#ifndef BASIC_COLLISION_SYSTEM_HEADER
#define BASIC_COLLISION_SYSTEM_HEADER

#include <world/world.h>
#include <component_base/component_handle.h>

#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/speed_component.h>
#include <generated/components/data_components/facing_side_component.h>
#include <generated/components/basic_components/solid_component.h>
#include <generated/components/basic_components/solid_component.h>
#include <generated/components/basic_components/default_collision_armor_component.h>

class BasicCollisionSystem : public ImpulseSystem {
public:
	BasicCollisionSystem() {
		m_signature
			.add_component<TransformComponent>()
			.add_component<SpeedComponent>()
			.add_component<FacingSideComponent>()
			.add_component<SolidComponent>();

		m_signature_of_victim
			.add_component<SolidComponent>()
			.add_component<DefaultCollisionArmorComponent>();
	}
	void exchange_impulse(const Entity& initiator, const Entity& victim) override {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> facing_side;
		m_parent_world->unpack(initiator,
			transform,
			speed,
			facing_side);



		do_impulse(initiator,
			*transform,
			*speed,
			*facing_side,
			victim);
	}
private:

	void do_impulse(
		Entity initiator,
		TransformComponent& initiator_transform,
		SpeedComponent& initiator_speed,
		FacingSideComponent& initiator_facing_side,
		Entity victim);

};
#endif