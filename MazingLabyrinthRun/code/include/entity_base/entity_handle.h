#ifndef ENTITY_HANDLE_HEADER
#define ENTITY_HANDLE_HEADER

#include <entity_base/entity.h>
#include <component_base/component_handle.h>
#include <game.h>

struct EntityHandle {
	Entity entity;
	Game* game;

	void destroy() { game->destroy_entity(entity); }

	template<class... ComponentType>
	void add_components(std::unique_ptr<ComponentType>&&... component) {
		game->add_components(entity, std::forward <std::unique_ptr<ComponentType>>(component)...);
	}

	template<class... ComponentType>
	void add_components() { game->add_components<ComponentType...>(entity);}

	template<class... ComponentType>
	void add_event_components() { game->add_event_components<ComponentType...>(entity); }

	template<typename ComponentType>
	void remove_component() { game->remove_component<ComponentType>(entity); }

	template<typename ComponentType>
	ComponentHandle<ComponentType> get_component() { return std::get<0>(game->components->unpack<ComponentType>(entity)); }
};
#endif