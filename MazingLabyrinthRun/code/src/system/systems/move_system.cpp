#include "../include/system/systems/move_system.h"

#include "../include/component_base/component_handle.h"

void Move::update(float dt) {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> side;

		m_parent_world->unpack(entity, transform, side, speed);

		if (side->m_side == FacingSide::right)
			transform->m_position = {transform->m_position.x + (speed->m_speed * dt), transform->m_position.y};
		if (side->m_side == FacingSide::left)
			transform->m_position = {transform->m_position.x - (speed->m_speed * dt), transform->m_position.y};
		if (side->m_side == FacingSide::up)
			transform->m_position = {transform->m_position.x , transform->m_position.y - (speed->m_speed * dt)};
		if (side->m_side == FacingSide::down)
			transform->m_position = {transform->m_position.x , transform->m_position.y + (speed->m_speed * dt)};
	}
}