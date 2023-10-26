#include <world/world.h>

#include <generated/components/data_components/transform_component.h>
#include <entity_base/entity_handle.h>

#include <iostream>

namespace {
void update_mask_in_systems(Entity const& entity,
                            ComponentMask& new_mask,
                            ComponentMask& old_mask,
                            EntityTrackerSystem* system) {
	ComponentMask systemSignature = system->get_signature();
	if (new_mask.is_new_match(old_mask, systemSignature))
		system->register_entity(entity);
	else if (new_mask.is_no_longer_matched(old_mask, systemSignature))
		system->unregister_entity(entity);
}
} // namespace

World::World(std::unique_ptr<EntityManager> entity_manager) : m_entity_manager(std::move(entity_manager)) {}

void World::init() {
	for (auto& system : m_producer_system_sequence_wrapper.get_systems()) { system->init(); }
}

void World::update(float dt) { m_producer_system_sequence_wrapper.run_systems(dt); }

void World::render() { 
	for (auto& system : m_render_systems) system->render();
}

EntityHandle World::create_entity() { return {m_entity_manager->create_entity(), this}; }

void World::destroy_entity(Entity entity) {
	for (auto& system : m_producer_system_sequence_wrapper.get_systems()) 
		if (m_entity_masks[entity].matches(system->get_signature()))
			system->unregister_entity(entity); 

	for (auto& component_manager : m_component_managers) 
		component_manager->destroy_component(entity);
	
	m_entity_masks[entity] = {};

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
World* World::add_render_system(std::unique_ptr<RenderSystem>&& system) {
	system->register_world(this);
	m_render_systems.push_back(std::move(system));
	return this;
} 


void World::update_entity_mask(Entity const& entity, ComponentMask old_mask) {
	ComponentMask new_mask = m_entity_masks[entity];
	for (auto& system : m_producer_system_sequence_wrapper.get_systems()) 
		update_mask_in_systems(entity, new_mask, old_mask, system.get());
	for (auto& system :m_render_systems)
		update_mask_in_systems(entity, new_mask, old_mask, system.get());
	
}

void World::react_on_event(Entity const& entity, ComponentMask new_mask) {
	for (auto& system : m_react_systems)
		if (new_mask.matches(system->get_signature())) system->react(entity);
}

bool World::place_entity(EntityHandle& entity, sf::Vector2f position) {
	entity.get_component<TransformComponent>()->position = position;
	return true;
}

void World::exchange_impulses(Entity const& initiator, Entity const& victim) {
	for (auto& system : m_impulse_systems) {
		if (m_entity_masks[initiator].matches(system->get_signature()) &&
		    m_entity_masks[victim].matches(system->get_signature_of_victim()))
			system->exchange_impulse(initiator, victim);
	}
}
