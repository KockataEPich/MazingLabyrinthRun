#include "../include/system/systems/ai_system.h"

#include "../include/component_base/component_handle.h"

void AI::update(float dt) {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> side;

		m_parent_world->unpack(entity, transform, side, speed);
		float delta_x = m_parent_world->get_player_location().x - transform->m_position.x;
		float delta_y = m_parent_world->get_player_location().y - transform->m_position.y;

		if (delta_x == 0 && delta_y == 0) continue;

		if (delta_x != 0) {
			if (delta_x > 0)  // right
				transform->m_position = {transform->m_position.x + speed->m_speed , transform->m_position.y};
			else  // left
				transform->m_position = {transform->m_position.x - speed->m_speed, transform->m_position.y};
		}

		if (delta_y != 0) {
			if (delta_y < 0)  // up
				transform->m_position = {transform->m_position.x, transform->m_position.y - speed->m_speed};
			else  // down
				transform->m_position = {transform->m_position.x, transform->m_position.y + speed->m_speed};
		}
	}
}