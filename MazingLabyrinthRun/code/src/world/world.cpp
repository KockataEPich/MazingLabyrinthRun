#include <world/world.h>

#include <components/data_components/transform_component.h>
#include <entity_base/entity_handle.h>

#include <iostream>

World::World(std::unique_ptr<EntityManager> entityManager) : m_entity_manager(std::move(entityManager)) {}

void World::init() {
	for (auto& system : m_producer_system_sequence_wrapper.get_systems()) { system->init(); }
}

void World::update(float dt) { m_producer_system_sequence_wrapper.run_systems(dt); }

// Last system is always the render system. It behaves like producer systems, however needs to be tick independent
// and has to be executed at a different position
void World::render() { m_producer_system_sequence_wrapper.get_systems().back()->update(); }

EntityHandle World::create_entity() { return {m_entity_manager->create_entity(), this}; }

void World::destroy_entity(Entity entity) {
	for (auto& system : m_producer_system_sequence_wrapper.get_systems()) { system->unregister_entity(entity); }
	m_entity_manager->destroy(entity);
}

World* World::add_producer_system(std::unique_ptr<ProducerSystem>&& system) {
	system->register_world(this);
	m_producer_system_sequence_wrapper.add_system(std::move(system));
	return this;
}

World* World::add_react_system(std::unique_ptr<ReactSystem>&& system) {
	system->register_world(this);
	m_react_systems.push_back(std::move(system));
	return this;
}

World* World::add_impulse_system(std::unique_ptr<ImpulseSystem>&& system) {
	system->register_world(this);
	m_impulse_systems.push_back(std::move(system));
	return this;
}

void World::update_entity_mask(Entity const& entity, ComponentMask old_mask) {
	ComponentMask new_mask = m_entity_masks[entity];
	for (auto& system : m_producer_system_sequence_wrapper.get_systems()) {
		ComponentMask systemSignature = system->get_signature();
		if (new_mask.is_new_match(old_mask, systemSignature))
			system->register_entity(entity);
		else if (new_mask.is_no_longer_matched(old_mask, systemSignature))
			system->unregister_entity(entity);
	}
}

void World::react_on_event(Entity const& entity, ComponentMask new_mask) {
	for (auto& system : m_react_systems)
		if (new_mask.matches(system->get_signature())) system->react(entity);
}

bool World::place_entity(EntityHandle& entity, sf::Vector2f position) {
	entity.get_component<TransformComponent>()->m_position = position;
	return true;
}

void World::exchange_impulses(Entity const& initiator, Entity const& victim) {
	for (auto& system : m_impulse_systems) {
		if (m_entity_masks[initiator].matches(system->get_signature()) &&
		    m_entity_masks[victim].matches(system->get_signature_of_victim()))
			system->exchange_impulse(initiator, victim);
	}
}
