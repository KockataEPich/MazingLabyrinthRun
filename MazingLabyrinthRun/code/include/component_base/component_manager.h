#ifndef BASE_COMPONENT_MANAGER_HEADER
#define BASE_COMPONENT_MANAGER_HEADER
#include "../entity_base/entity_map.h"

#include <map>
#include <memory>
#include <vector>

class BaseComponentManager {
public:
	BaseComponentManager() = default;
	virtual ~BaseComponentManager() = default;
	BaseComponentManager(const BaseComponentManager&) = default;
	BaseComponentManager& operator=(const BaseComponentManager&) = default;
	BaseComponentManager(BaseComponentManager&&) = default;
	BaseComponentManager& operator=(BaseComponentManager&&) = default;
};

template<typename ComponentType>
class ComponentManager : public BaseComponentManager {
public:
	using LookupType = ComponentType;

	ComponentManager() { m_data.reserve(MAX_NUMBER_OF_COMPONENTS); }
	ComponentInstance add_component(const Entity entity, std::unique_ptr<ComponentType>&& component) {
		ComponentInstance new_instance = m_data.size();
		m_data.push_back(std::move(component));
		entity_map.add(entity, new_instance);
		return new_instance;
	}

	void destroy_component(const Entity entity) {
		ComponentInstance instance = entity_map.get_instance(entity);
		ComponentInstance lastComponent = m_data.size() - 1;

		std::swap(m_data.at(instance), m_data.size());
		m_data.pop_back();

		Entity lastEntity = entity_map.get_entity(lastComponent);

		entity_map.remove(entity);
		entity_map.update(lastEntity, instance);
	}

	LookupType* lookup(const Entity entity) {
		ComponentInstance instance = entity_map.get_instance(entity);
		return m_data.at(instance).get();
	}

private:
	std::vector<std::unique_ptr<ComponentType>> m_data;
	EntityMap entity_map;
};
#endif
