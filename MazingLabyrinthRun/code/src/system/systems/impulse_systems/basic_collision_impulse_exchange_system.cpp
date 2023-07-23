#include <system/systems/impulse_systems/basic_collision_impulse_exchange_system.h>
#include <component_base/component_handle.h>


sf::Vector2f change_transform_on_side(TransformComponent& transform, const SpeedComponent& speed, FacingSideComponent& side) { 
	switch (side.m_side) {
		case FacingSide::right:return {transform.m_position.x - speed.m_speed * 2, transform.m_position.y};
		case FacingSide::left: return {transform.m_position.x + speed.m_speed * 2, transform.m_position.y};
	}
}


void BasicCollisionImpulseExchange::exchange_impulse(const Entity& initiator, const Entity& victim) {
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<SpeedComponent> speed;
	ComponentHandle<FacingSideComponent> side;

	m_parent_world->unpack(initiator, transform, side, speed);
	transform->m_position = change_transform_on_side(*transform, *speed, *side);
} 