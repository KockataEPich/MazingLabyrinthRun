#ifndef ENTITY_HANDLE_HEADER
#define ENTITY_HANDLE_HEADER

#include "../component/componentHandle.h"
#include "../world/world.h"
#include "entity.h"

struct EntityHandle {
	Entity entity;
	World* world;

	void destroy() { world->destroy_entity(entity); }

	template<typename ComponentType>
	void add_component(ComponentType&& component) {
		world->add_component<ComponentType>(entity, std::forward<ComponentType>(component));
	}

	template<typename ComponentType>
	void remove_component() {
		world->remove_component<ComponentType>(entity);
	}

	template<typename ComponentType>
	ComponentHandle<ComponentType> get_component() {
		ComponentHandle<ComponentType> handle;
		world->unpack(entity, handle);
		return handle;
	}
};
#endif