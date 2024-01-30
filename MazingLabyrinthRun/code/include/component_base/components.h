#ifndef COMPONENTS_HEADER
#define COMPONENTS_HEADER

#include <component_base/component_handle.h>
#include <component_base/component_manager.h>
#include <component_base/component_mask.h>

#include <memory>

class Game;

class Components {
public:
	Components(Game* game) : m_game{game} {};
	void init(){};

	template<typename ComponentType>
	void add_component(Entity const& entity, std::unique_ptr<ComponentType>&& component) {
			ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
			manager->add_component(entity, std::move(component));
	}

	template<typename ComponentType>
	void remove_component(Entity const& entity) {
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		ComponentHandle<ComponentType> component{entity, manager->lookup(entity), manager};
		component.destroy();
	}

	template<class... ComponentType>
	auto unpack(const Entity& entity) {
		return std::make_tuple(get_component_handle<ComponentType>(entity)...);
	}

	template<typename ComponentType>
	void add_custom_component_manager(std::unique_ptr<ComponentManager<ComponentType>> manager) {
		int family = GetComponentFamily<ComponentType>();
		if (family >= m_component_managers.size()) { m_component_managers.resize(family + 1); }
		m_component_managers[family] = manager;
	}

	void remove_all_entity_components(const Entity entity);

private:
	std::vector<std::unique_ptr<BaseComponentManager>> m_component_managers;

	Game* m_game;

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

	template<class ComponentType>
	ComponentHandle<ComponentType> get_component_handle(const Entity entity) {
		auto manger = get_component_manager<ComponentType>();
		return ComponentHandle<ComponentType>(entity, manger->lookup(entity), manger);
	}

};

#endif