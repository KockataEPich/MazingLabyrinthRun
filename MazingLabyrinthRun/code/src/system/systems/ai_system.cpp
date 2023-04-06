#include "../include/system/systems/ai_system.h"

#include "../include/component_base/component_handle.h"
#include "../include/event/events/event_types/move_event.h"

void AI::update() {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> side;

		m_parent_world->unpack(entity, transform, side, speed);
		float delta_x = m_parent_world->get_player_location().x - transform->m_position.x;
		float delta_y = m_parent_world->get_player_location().y - transform->m_position.y;

		if (delta_x == 0 && delta_y == 0) continue;

		if (delta_x != 0) {
			if (delta_x > 0) RunRight{*transform, *speed, *side}.happen();
			else RunLeft{*transform, *speed, *side}.happen();
		}

		if (delta_y != 0) {
			if (delta_y < 0) RunUp{*transform, *speed, *side}.happen();
			else RunDown{*transform, *speed, *side}.happen();  
	
		}

		//if(in_range(m_parent_world)
			//atack(m_parent_player);
	}
}