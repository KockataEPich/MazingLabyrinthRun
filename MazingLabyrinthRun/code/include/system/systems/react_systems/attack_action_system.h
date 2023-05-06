#ifndef ATTACK_ACTION_SYSTEM_HEADER
#define ATTACK_ACTION_SYSTEM_HEADER

#include <components/data_components/facing_side_component.h>
#include <components/data_components/transform_component.h>
#include <components/data_components/action_type_component.h>
#include <components/event_components/initiate_action_component.h>

#include <world/world.h>
#include <system/system.h>
class AttackActionSystem : public ReactSystem {
public:
	AttackActionSystem() {
		m_signature.add_component<TransformComponent>()
		    .add_component<ActionTypeComponent>()
		    .add_component<FacingSideComponent>()
		    .add_component<InitiateActionEventComponent>();
	}
	virtual void react(Entity const& entity);
};

#endif