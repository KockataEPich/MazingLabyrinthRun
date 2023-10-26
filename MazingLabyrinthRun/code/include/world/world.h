#ifndef WORLD_HEADER_H
#define WORLD_HEADER_H

#include "../component_base/component_handle.h"
#include "../component_base/component_manager.h"
#include "../entity_base/entity_manager.h"
#include "../entity_creation/entity_list.h"
#include "../system/system.h"
#include "../system/system_sequence_wrapper.h"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <any>
#include <memory>

struct EntityHandle;
class World {
public:
	explicit World(std::unique_ptr<EntityManager> entity_manager);

	void init();

	void update(float dt);
	void render();

	EntityHandle create_entity();

	World* add_producer_system(std::unique_ptr<ProducerSystem>&& system);
	World* add_react_system(std::unique_ptr<ReactSystem>&& system);
	World* add_impulse_system(std::unique_ptr<ImpulseSystem>&& system);
	World* add_render_system(std::unique_ptr<RenderSystem>&& system);

	void destroy_entity(Entity entity);
	bool place_entity(EntityHandle& handle, sf::Vector2f position);
	void exchange_impulses(Entity const& initiator, Entity const& victim);

	template<typename ComponentType>
	void add_custom_component_manager(std::unique_ptr<ComponentManager<ComponentType>> manager) {
		int family = GetComponentFamily<ComponentType>();
		if (family >= m_component_managers.size()) { m_component_managers.resize(family + 1); }
		m_component_managers[family] = manager;
	}

	template<typename ComponentType>
	void add_component(Entity const& entity, std::unique_ptr<ComponentType>&& component) {
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		manager->add_component(entity, std::move(component));

		ComponentMask oldMask = m_entity_masks[entity];
		m_entity_masks[entity].add_component<ComponentType>();

		update_entity_mask(entity, oldMask);
	}

	template<typename ComponentType>
	void add_event_component(Entity const& entity, std::unique_ptr<ComponentType>&& component) {
		ComponentMask old_mask = m_entity_masks[entity];
		ComponentMask new_mask = old_mask.add_component<ComponentType>();
		react_on_event(entity, new_mask);
	}

	template<typename ComponentType>
	void remove_component(Entity const& entity) {
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		ComponentHandle<ComponentType> component{entity, manager->lookup(entity), manager};
		component.destroy();

		ComponentMask oldMask = m_entity_masks[entity];
		m_entity_masks[entity].remove_component<ComponentType>();

		update_entity_mask(entity, oldMask);
	}

	template<typename ComponentType, typename... Args>
	void unpack(Entity e, ComponentHandle<ComponentType>& handle, ComponentHandle<Args>&... args) {
		unpack(e, handle);
		unpack<Args...>(e, args...);
	}

	// Base case
	template<typename ComponentType>
	void unpack(Entity e, ComponentHandle<ComponentType>& handle) {
		typedef ComponentManager<ComponentType> ComponentManagerType;
		auto manger = get_component_manager<ComponentType>();
		handle = ComponentHandle<ComponentType>(e, manger->lookup(e), manger);
	}

	void set_player_location(sf::Sprite* player_sprite) { m_player_sprite = player_sprite; }
	const sf::Sprite& get_player_sprite() { return *m_player_sprite; }

	template<typename ComponentType>
	const std::vector<Entity> get_all_entities_who_have_component() {
		std::vector<Entity> entity_vector;
		ComponentMask component_mask;
		component_mask.add_component<ComponentType>();
		for (auto& [entity, mask] : m_entity_masks)
			if (mask.matches(component_mask)) entity_vector.push_back(entity);
		return entity_vector;
	}

private:
	std::unique_ptr<EntityManager> m_entity_manager;

	std::vector<std::unique_ptr<ReactSystem>> m_react_systems;
	std::vector<std::unique_ptr<ImpulseSystem>> m_impulse_systems;
	std::vector<std::unique_ptr<RenderSystem>> m_render_systems;
	ProducerSystemSequenceWrapper m_producer_system_sequence_wrapper;

	std::vector<std::unique_ptr<BaseComponentManager>> m_component_managers;
	std::map<Entity, ComponentMask> m_entity_masks;
	
	sf::Sprite* m_player_sprite;

	void update_entity_mask(Entity const& entity, ComponentMask old_mask);
	void react_on_event(Entity const& entity, ComponentMask new_mask);

	std::unordered_map<int, int> m_managers_family_to_index;
	int m_current_manager_last_index = 0;

	template<typename ComponentType>
	ComponentManager<ComponentType>* get_component_manager() {
		int family = get_component_family<ComponentType>();

		if (m_managers_family_to_index.find(family) == m_managers_family_to_index.end()) {
			m_managers_family_to_index[family] = m_current_manager_last_index++;
		}

		const int index = m_managers_family_to_index[family];
		if (index >= m_component_managers.size()) { m_component_managers.resize(m_current_manager_last_index); }

		if (!m_component_managers[index]) {
			m_component_managers[index] = std::make_unique<ComponentManager<ComponentType>>();
		}

		return static_cast<ComponentManager<ComponentType>*>(m_component_managers[index].get());
	}
};
#endif