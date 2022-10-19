#ifndef ENTITY_HANDLE_HEADER
#define ENTITY_HANDLE_HEADER

#include "../component/componentHandle.h"
#include "../world/world.h"
#include "entity.h"

struct EntityHandle {
	Entity entity;
	World* world;

	void destroy() { world->destroyEntity(entity); }

	template<typename ComponentType>
	void addComponent(ComponentType&& component) {
		world->addComponent<ComponentType>(entity, std::forward<ComponentType>(component));
	}

	template<typename ComponentType>
	void removeComponent() {
		world->removeComponent<ComponentType>(entity);
	}

	template<typename ComponentType>
	ComponentHandle<ComponentType> getComponent() {
		ComponentHandle<ComponentType> handle;
		world->unpack(entity, handle);
		return handle;
	}
};
#endif