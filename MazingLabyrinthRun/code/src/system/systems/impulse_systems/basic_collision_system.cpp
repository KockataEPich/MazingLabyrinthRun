#include <generated/systems/impulse_systems/basic_collision_system.h>

namespace {
sf::Vector2f
    change_transform_on_side(TransformComponent& transform, const SpeedComponent& speed, FacingSideComponent& side) {
	switch (side.side) {
		case FacingSide::right: return {transform.position.x - speed.speed * 2, transform.position.y};
		case FacingSide::left: return {transform.position.x + speed.speed * 2, transform.position.y};
	}
}

}  // namespace

void BasicCollisionSystem::clash_entities(
	Entity initiator,
	TransformComponent& initiator_transform,
	SpeedComponent& initiator_speed,
	FacingSideComponent& initiator_facing_side,
	Entity victim){ 


	initiator_transform.position =
	    change_transform_on_side(initiator_transform, initiator_speed, initiator_facing_side);
}

