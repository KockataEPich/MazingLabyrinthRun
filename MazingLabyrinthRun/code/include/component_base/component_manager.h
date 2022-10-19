#ifndef BASE_COMPONENT_MANAGER_HEADER
#define BASE_COMPONENT_MANAGER_HEADER
#include "../entity_base/entity_map.h"

#include <array>
#include <map>

template<typename ComponentType>
struct ComponentData {
	unsigned int size = 1;
	std::array<ComponentType, MAX_NUMBER_OF_COMPONENTS>* data;
};

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

	ComponentManager() {
		component_data.data = static_cast<std::array<ComponentType, 1024>*>(malloc(sizeof(ComponentType) * 1024));
	}
	ComponentInstance add_component(Entity entity, ComponentType& component) {
		ComponentInstance new_instance = component_data.size;
		component_data.data->at(new_instance) = component;
		entity_map.add(entity, new_instance);
		component_data.size++;
		return new_instance;
	}

	void destroy_component(Entity entity) {
		ComponentInstance instance = entity_map.get_instance(entity);

		ComponentInstance lastComponent = component_data.size - 1;
		component_data.data[instance] = component_data.data[lastComponent];
		Entity lastEntity = entity_map.get_entity(lastComponent);

		entity_map.remove(entity);
		entity_map.update(lastEntity, instance);

		component_data.size--;
	}

	LookupType* lookup(Entity entity) {
		ComponentInstance instance = entity_map.get_instance(entity);
		return &component_data.data->at(instance);
	}

private:
	ComponentData<ComponentType> component_data;
	EntityMap entity_map;
};
#endif
