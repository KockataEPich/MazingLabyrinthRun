#include "../include/system/systems/ai_system.h"

#include "../include/component_base/component_handle.h"
#include "../include/components/move_event_component.h"

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
			if (delta_x > 0) side->m_side = FacingSide::right;
			else side->m_side = FacingSide::left;
			m_parent_world->add_component(entity, std::make_unique<MoveEventComponent>());
		}
		if (delta_y != 0) {
			if (delta_y < 0) side->m_side = FacingSide::up;
			else side->m_side = FacingSide::down;
			m_parent_world->add_component(entity, std::make_unique<MoveEventComponent>());
		}

		
	}
}