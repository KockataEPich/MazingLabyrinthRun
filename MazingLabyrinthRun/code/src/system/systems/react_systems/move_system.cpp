#include <system/systems/react_systems/move_system.h>

#include <component_base/component_handle.h>
#include <components/event_components/check_collision_event_component.h>

namespace {
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
}  // namespace

void Move::react(Entity const& entity) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> side;

		m_parent_world->unpack(entity, transform, side, speed);
	    transform->m_position = calculate_new_position(*transform, *speed, *side);
	    m_parent_world->add_event_component(entity, std::make_unique<CheckCollisionEventComponent>());
}