#ifndef ENTITY_HANDLE_HEADER
#define ENTITY_HANDLE_HEADER

#include "../world/world.h"

struct EntityHandle {
	Entity entity;
	World* world;

	void destroy() { world->destroy_entity(entity); }

	template<typename ComponentType>
	EntityHandle& add_component(std::unique_ptr<ComponentType>&& component) {
		world->add_component<ComponentType>(entity, std::move(component));
		return *this;
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