#include "../include/world/world.h"

#include "../include/entity_base/entity_handle.h"

#include <iostream>

World::World(std::unique_ptr<EntityManager> entityManager) : m_entity_manager(std::move(entityManager)) {}

void World::init() {
	for (auto& system : m_systems) { system->init(); }
}

void World::update(float dt) {
	for (auto& system : m_systems) { system->update(dt); }
}

void World::render() {
	for (auto& system : m_systems) { system->render(); }
}

EntityHandle World::create_entity() { return {m_entity_manager->create_entity(), this}; }

void World::destroy_entity(Entity entity) {
	for (auto& system : m_systems) { system->unregister_entity(entity); }

	m_entity_manager->destroy(entity);
}

void World::add_system(std::unique_ptr<System> system) {
	system->register_world(this);
	m_systems.push_back(std::move(system));
}

void World::update_entity_mask(Entity const& entity, ComponentMask old_mask) {
	ComponentMask new_mask = m_entity_masks[entity];

	for (auto& system : m_systems) {
		ComponentMask systemSignature = system->get_signature();
		if (new_mask.is_new_match(old_mask, systemSignature)) {
			system->register_entity(entity);
		} else if (new_mask.is_no_longer_matched(old_mask, systemSignature)) {
			system->unregister_entity(entity);
		}
	}
}
