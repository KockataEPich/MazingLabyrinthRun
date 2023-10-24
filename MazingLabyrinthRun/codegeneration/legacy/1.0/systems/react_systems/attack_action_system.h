// ################## THIS FILE IS GENERATED ##################
#ifndef ATTACK_ACTION_SYSTEM_HEADER
#define ATTACK_ACTION_SYSTEM_HEADER

#include <world/world.h>

#include <generated/components/data_components/action_type_component.h>
#include <generated/components/data_components/facing_side_component.h>
#include <generated/components/basic_components/initiate_action_component.h>
#include <generated/components/data_components/transform_component.h>

class AttackActionSystem : public ReactSystem {
public:
	AttackActionSystem() {
		m_signature
			.add_component<ActionTypeComponent>()
			.add_component<FacingSideComponent>()
			.add_component<InitiateActionComponent>()
			.add_component<TransformComponent>();
	}
	void react(const Entity& entity) override {
		ComponentHandle<ActionTypeComponent> action_type;
		ComponentHandle<FacingSideComponent> facing_side;
		ComponentHandle<TransformComponent> transform;
		m_parent_world->unpack(entity,
			action_type,
			facing_side,
			transform);

		react_on_entity(Entity entity,
			*action_type,
			*facing_side,
			*transform);
	}
private:

	void react_on_entity(Entity entity,
		ActionTypeComponent& action_type,
		FacingSideComponent& facing_side,
		InitiateActionComponent& initiate_action,
		TransformComponent& transform);

};
#endif