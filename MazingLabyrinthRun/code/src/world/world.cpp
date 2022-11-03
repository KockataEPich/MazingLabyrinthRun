#include "../include/world/world.h"

#include "../include/components/transform_component.h"
#include "../include/entity_base/entity_handle.h"

#include <iostream>

namespace {
void flow_entity(Entity const& entity,
                 const std::vector<std::unique_ptr<System>>& systems,
                 ComponentMask new_mask,
                 ComponentMask old_mask) {
	for (auto& system : systems) {
		ComponentMask systemSignature = system->get_signature();
		if (new_mask.is_new_match(old_mask, systemSignature))
			system->register_entity(entity);
		else if (new_mask.is_no_longer_matched(old_mask, systemSignature))
			system->unregister_entity(entity);
	}
}
}  // namespace
World::World(std::unique_ptr<EntityManager> entityManager) : m_entity_manager(std::move(entityManager)) {}

void World::init() {
	for (auto& system : m_systems) { system->init(); }
}

void World::update(float dt) {
	for (auto& system : m_systems) { system->update(dt); }
}

void World::render() {
	for (auto& system : m_render_systems) { system->render(); }
}

EntityHandle World::create_entity() { return {m_entity_manager->create_entity(), this}; }

void World::destroy_entity(Entity entity) {
	for (auto& system : m_systems) { system->unregister_entity(entity); }

	m_entity_manager->destroy(entity);
}

World* World::add_system(std::unique_ptr<System> system) {
	system->register_world(this);
	m_systems.push_back(std::move(system));
	return this;
}

void World::add_render_system(std::unique_ptr<System> render_system) {
	render_system->register_world(this);
	m_render_systems.push_back(std::move(render_system));
}

void World::update_entity_mask(Entity const& entity, ComponentMask old_mask) {
	ComponentMask new_mask = m_entity_masks[entity];

	flow_entity(entity, m_systems, new_mask, old_mask);
	flow_entity(entity, m_render_systems, new_mask, old_mask);
}

bool World::place_entity(EntityHandle& entity, sf::Vector2f position) {
	entity.get_component<TransformComponent>()->m_position = position;
	return true;
}
