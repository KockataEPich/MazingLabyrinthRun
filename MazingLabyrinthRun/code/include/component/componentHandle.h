#ifndef COMPONENT_HANDLE_HEADER
#define COMPONENT_HANDLE_HEADER
#include "../include/entity/entity.h"
#include "componentManager.h"

template<typename ComponentType>
struct ComponentHandle {
	using ExposedComponentType = typename ComponentManager<ComponentType>::LookupType;

	Entity owner;
	ExposedComponentType* component;
	ComponentManager<ComponentType>* manager;

	// Empty constructor used for World::unpack()
	ComponentHandle(){};
	ComponentHandle(Entity owner, ExposedComponentType* component, ComponentManager<ComponentType>* manager) {
		this->owner = owner;
		this->component = component;
		this->manager = manager;
	}

	// handle->member is the same as handle.component->member
	ExposedComponentType* operator->() const { return component; }

	void destroy() { manager->destroyComponent(owner); }
};
#endif