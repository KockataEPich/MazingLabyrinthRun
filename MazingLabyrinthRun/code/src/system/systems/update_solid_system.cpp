#include "../include/system/systems/update_solid_system.h"
#include "../include/component_base/component_handle.h"

void UpdateSolid::react(const Entity& entity) {
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<SpriteComponent> sprite;
	ComponentHandle<SolidComponent> solid;

	m_parent_world->unpack(entity, transform, solid, sprite);

	sprite->m_sprite.setPosition(transform->m_position);
	sprite->m_sprite.setScale(transform->m_scale);
	solid->m_hitbox = sprite->m_sprite.getGlobalBounds();
	solid->m_hitbox.height -= 100;
	solid->m_hitbox.width -= 30;
	solid->m_hitbox.top += 60;
	solid->m_hitbox.left += 13;
}
