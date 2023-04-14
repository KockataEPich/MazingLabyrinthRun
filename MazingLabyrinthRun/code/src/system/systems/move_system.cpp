#include "../include/system/systems/move_system.h"

#include "../include/component_base/component_handle.h"
#include "../include/components/collision_component.h"
#include "../include/components/update_solid_event_component.h"
sf::Vector2<float> calculate_new_position(const TransformComponent& transform,
										  const SpeedComponent& speed,
                                          const FacingSideComponent& facing_side) {
	switch (facing_side.m_side) { 
		case FacingSide::right: return {transform.m_position.x + speed.m_speed, transform.m_position.y};
		case FacingSide::left: return {transform.m_position.x - speed.m_speed, transform.m_position.y};
		case FacingSide::up: return {transform.m_position.x, transform.m_position.y - speed.m_speed};
		case FacingSide::down: return {transform.m_position.x, transform.m_position.y + speed.m_speed};
	}
}

void Move::react(Entity const& entity) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> side;

		m_parent_world->unpack(entity, transform, side, speed);
	    transform->m_position = calculate_new_position(*transform, *speed, *side);
	    m_parent_world->add_event_component(entity, std::make_unique<UpdateSolidEventComponent>());
	    m_parent_world->add_event_component(entity, std::make_unique<CollisionComponent>());
}