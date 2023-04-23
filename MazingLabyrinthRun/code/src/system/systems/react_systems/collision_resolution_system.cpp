#include <system/systems/react_systems/collision_resolution_system.h>
#include <component_base/component_handle.h>
#include <components/event_components/update_solid_event_component.h>

sf::Vector2f change_transform_on_side(TransformComponent& transform, const SpeedComponent& speed, FacingSideComponent& side) { 
	switch (side.m_side) {
		case FacingSide::right:return {transform.m_position.x - speed.m_speed * 3, transform.m_position.y};
		case FacingSide::left: return {transform.m_position.x + speed.m_speed * 3, transform.m_position.y};
		case FacingSide::up: return {transform.m_position.x, transform.m_position.y + speed.m_speed * 3};
		case FacingSide::down: return {transform.m_position.x, transform.m_position.y - speed.m_speed * 3};
	}
}

void CollisionResolution::react(Entity const& entity) {
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<SpeedComponent> speed;
	ComponentHandle<FacingSideComponent> side;

	m_parent_world->unpack(entity, transform, side, speed);
	transform->m_position = change_transform_on_side(*transform, *speed, *side);
} 