#include <system/systems/react_systems/update_solid_system.h>
#include <component_base/component_handle.h>

void UpdateSolid::react(const Entity& entity) {
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<SolidComponent> solid;

	m_parent_world->unpack(entity, transform, solid);

	// shave off 5% of each side
	
	solid->m_hitbox = {transform->m_position.x - 30,
					   transform->m_position.y + 15,
	                   get_scaled_size(*transform).x - 30,
		               get_scaled_size(*transform).y - 100};
}