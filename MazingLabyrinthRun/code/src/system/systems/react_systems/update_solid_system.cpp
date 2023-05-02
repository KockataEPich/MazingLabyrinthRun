#include <system/systems/react_systems/update_solid_system.h>
#include <component_base/component_handle.h>

void UpdateSolid::react(const Entity& entity) {
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<SolidComponent> solid;

	m_parent_world->unpack(entity, transform, solid);

	// shave off 5% of each sid
	auto scaled_size = get_scaled_size(*transform);
	solid->m_hitbox = { transform->m_position.x - scaled_size.x * 0.275f,
	                   transform->m_position.y - scaled_size.y * 0.10f,
	                   scaled_size.x * 0.55f,
	                   scaled_size.y * 0.50f};
}