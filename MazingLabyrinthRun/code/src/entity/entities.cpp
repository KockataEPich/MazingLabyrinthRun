#include <entity_base/entities.h>
#include <game.h>

void Entities::delete_entity(const Entity entity) {
	m_entity_masks[entity] = {};
	m_entity_manager->destroy(entity);
}