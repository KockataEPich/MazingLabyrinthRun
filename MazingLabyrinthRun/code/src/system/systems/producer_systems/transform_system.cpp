#include <generated/systems/producer_systems/transform_system.h>
void TransformSystem::for_every_entity(
	Entity entity,
	TransformComponent& transform,
	SpriteComponent& sprite){ 
	sprite.sprite.setPosition(transform.position);
	sprite.sprite.setScale(transform.scale);
}

