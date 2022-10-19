#ifndef COMPONENT_HANDLE_HEADER
#define COMPONENT_HANDLE_HEADER

#include "component_manager.h"

template<typename ComponentType>
struct ComponentHandle {
	using ExposedComponentType = typename ComponentManager<ComponentType>::LookupType;

	Entity m_owner;
	ExposedComponentType* m_component;
	ComponentManager<ComponentType>* m_manager;

	ComponentHandle(){};
	ComponentHandle(Entity owner, ExposedComponentType* component, ComponentManager<ComponentType>* manager) {
		this->m_owner = owner;
		this->m_component = component;
		this->m_manager = manager;
	}

	// handle->member is the same as handle.component->member
	ExposedComponentType* operator->() const { return m_component; }

	void destroy() { m_manager->destroyComponent(m_owner); }
};
#endif