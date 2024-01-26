#include <component_base/components.h>

void Components::remove_all_entity_components(const Entity entity) {
		for (auto& component_manager : m_component_managers)
		component_manager->destroy_component(entity);
}