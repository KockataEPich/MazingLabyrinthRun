#include <system/systems/react_systems/move_system.h>

#include <component_base/component_handle.h>
#include <components/event_components/check_collision_event_component.h>
#include <numbers> // std::numbers

namespace {

sf::Vector2f change_transform_depending_on_target_vector(const TransformComponent& transform,
	const SpeedComponent& speed,
	sf::Vector2f target) {

	sf::Vector2f triangle_sides = {std::abs(transform.m_position.x - target.x),
	                               std::abs(transform.m_position.y - target.y)};

	auto atan_val = std::atan2(triangle_sides.y, triangle_sides.x);
	auto angle = atan_val * 180 / std::numbers::pi;

	auto x_offset = speed.m_speed * std::cos(std::numbers::pi * 2 * angle / 360);
	auto y_offset = speed.m_speed * std::sin(std::numbers::pi * 2 * angle / 360);

	auto new_x = (transform.m_position.x < target.x) ? transform.m_position.x + (float)x_offset 
													 : transform.m_position.x - (float)x_offset;

	auto new_y = (transform.m_position.y > target.y) ? transform.m_position.y + (float)y_offset
	                                                 : transform.m_position.y - (float)y_offset;

	return {new_x, new_y};
}

}  // namespace

void Move::react(Entity const& entity) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<TargetForDirection> target;

		m_parent_world->unpack(entity, transform, target, speed);
	    transform->m_position = change_transform_depending_on_target_vector(*transform, *speed, target->m_target_position);
	    m_parent_world->add_event_component(entity, std::make_unique<CheckCollisionEventComponent>());
}