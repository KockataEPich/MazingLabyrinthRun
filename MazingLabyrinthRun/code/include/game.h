#ifndef GAME_HEADER
#define GAME_HEADER

#include <window/game_window.h>

#include <entity_base/entities.h>
#include <system/systems.h>
#include <component_base/components.h>
#include <world/world.h>

struct EntityHandle;
class Game {
public:
	Game(GameWindow* window) : m_window{window} {}

	void init() { 
		entities->init();
		systems->init();
		components->init();
		world->init();
	}

	EntityHandle create_entity();

	void destroy_entity(const Entity entity) {
		systems->remove_entity_from_systems(entity);
		components->remove_all_entity_components(entity);
		entities->delete_entity(entity);
	}

	template<class... ComponentType>
	void add_components(const Entity& entity, std::unique_ptr<ComponentType>&&... component) {
		( [&] { 
			components->add_component(entity, std::move(component));
			ComponentMask old_mask = entities->get_mask(entity);
			entities->add_component_to_entity_mask<ComponentType>(entity);
			systems->update_entity_system_subscriptions(entity, old_mask);
		}(), ...);
	}

	template<typename ComponentType>
	void add_event_component(Entity const& entity, std::unique_ptr<ComponentType>&& component) {
		systems->react_on_event(entity, entities->get_mask(entity).add_component<ComponentType>());
	}

	template<class ComponentType>
	void remove_component(const Entity& entity) {
		components->remove_component<ComponentType>(entity);
		ComponentMask old_mask = entities->get_mask(entity);
		entities->remove_component_from_entity_mask<ComponentType>(entity);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	std::unique_ptr<Entities> entities = std::make_unique<Entities>(this);
	std::unique_ptr<Systems> systems = std::make_unique<Systems>(this);
	std::unique_ptr<Components> components = std::make_unique<Components>(this);
	std::unique_ptr<World> world = std::make_unique<World>(this);

	GameWindow* m_window;
};


#endif
