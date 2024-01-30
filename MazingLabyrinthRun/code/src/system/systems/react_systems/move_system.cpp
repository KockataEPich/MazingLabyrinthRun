#include <generated/systems/react_systems/move_system.h>

#include <numbers>  // for std::numbers::pi
#include <generated/components/basic_components/collision_check_component.h>

namespace {

sf::Vector2f change_transform_depending_on_target_vector(const TransformComponent& transform,
                                                         const SpeedComponent& speed,
                                                         sf::Vector2f target) {

	sf::Vector2f triangle_sides = {std::abs(transform.position.x - target.x),
	                               std::abs(transform.position.y - target.y)};

	auto atan_val = std::atan2(triangle_sides.y, triangle_sides.x);
	auto angle = atan_val * 180 / std::numbers::pi;

	auto x_offset = speed.speed * std::cos(std::numbers::pi * 2 * angle / 360);
	auto y_offset = speed.speed * std::sin(std::numbers::pi * 2 * angle / 360);

	auto new_x = (transform.position.x < target.x) ? transform.position.x + (float)x_offset
	                                                 : transform.position.x - (float)x_offset;

	auto new_y = (transform.position.y < target.y) ? transform.position.y + (float)y_offset
	                                                 : transform.position.y - (float)y_offset;

	return {new_x, new_y};
}

}  // namespace


void MoveSystem::react_on_entity(
	EntityHandle entity,
	TransformComponent& transform,
	SpeedComponent& speed,
	TargetForDirectionComponent& target_for_direction){ 

	transform.position =
	    change_transform_depending_on_target_vector(transform, speed, target_for_direction.target_position);
	entity.add_event_components<CollisionCheckComponent>();
}

