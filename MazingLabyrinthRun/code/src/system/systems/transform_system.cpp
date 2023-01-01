#include "../include/system/systems/transform_system.h"
#include "../include/component_base/component_handle.h"

void Transform::update(float dt) {
	for (auto& entity : m_registered_entities) {
		ComponentHandle<SpriteComponent> sprite;
		ComponentHandle<TransformComponent> transform;

		m_parent_world->unpack(entity, sprite, transform);

		sprite->m_sprite.setPosition(transform->m_position);
		sprite->m_sprite.setScale(transform->m_scale);
	}
}
