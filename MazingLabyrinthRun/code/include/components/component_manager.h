#ifndef COMPONENT_MANAGER_HEADER_H
#define COMPONENT_MANAGER_HEADER_H

#include "../entity/component.h"
#include "component_array.h"

#include <array>
#include <assert.h>
#include <bitset>
#include <numeric>
#include <unordered_map>

class ComponentManager {
public:
	template<typename T>
	void register_component() {
		const char* typeName = typeid(T).name();
		assert(m_component_types.find(typeName) == m_component_types.end() && "Registering component type more than once.");
		m_component_types.insert({typeName, m_next_component_type});
		m_component_arrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
		++m_next_component_type;
	}

	template<typename T>
	ComponentType get_component_type() {
		const char* typeName = typeid(T).name();
		assert(m_component_types.find(typeName) != m_component_types.end() && "Component not registered before use.");
		return m_component_types[typeName];
	}

	template<typename T>
	void add_component(Entity entity, T component) {
		get_component_array<T>()->insert_data(entity, component);
	}

	template<typename T>
	void remove_component(Entity entity) {
		// Remove a component from the array for an entity
		get_component_array<T>()->RemoveData(entity);
	}

	template<typename T>
	T& get_component(Entity entity) {
		return get_component_array<T>()->get_data(entity);
	}

	void entity_destroyed(Entity entity) {
		for (auto const& pair : m_component_arrays) {
			auto const& component = pair.second;
			component->entity_destroyed(entity);
		}
	}

private:
	std::unordered_map<const char*, ComponentType> m_component_types{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_component_arrays{};

	ComponentType m_next_component_type{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> get_component_array(){
		const char* typeName = typeid(T).name();
		assert(m_component_types.find(typeName) != m_component_types.end() && "Component not registered before use.");
		return std::static_pointer_cast<ComponentArray<T>>(m_component_arrays[typeName]);
	}
};

#endif