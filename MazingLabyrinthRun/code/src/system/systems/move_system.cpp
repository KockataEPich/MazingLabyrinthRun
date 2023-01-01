#include "../include/system/systems/move_system.h"

#include "../include/component_base/component_handle.h"



void Move::update(float dt) {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> side;
		ComponentHandle<ActionTypeComponent> action_type;
		ComponentHandle<CompositeEventComponent> events;

		m_parent_world->unpack(entity, transform, side, speed, action_type);

	}
}