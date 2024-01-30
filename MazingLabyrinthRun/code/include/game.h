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
	void add_components(const Entity& entity) {
		ComponentMask old_mask = entities->get_mask(entity);
		( [&] {
			    components->add_component(entity, std::make_unique<ComponentType>());
			    entities->add_component_to_entity_mask<ComponentType>(entity);
			    
		}(), ...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	template<class... ComponentType>
	void add_components(const Entity& entity, std::unique_ptr<ComponentType>&&... component) {
		ComponentMask old_mask = entities->get_mask(entity);
		( [&] { 
			components->add_component(entity, std::move(component));
			entities->add_component_to_entity_mask<ComponentType>(entity);
		}(), ...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	template<typename... ComponentType>
	void add_event_components(const Entity& entity) {
		( [&] { 
			auto new_mask = entities->get_mask(entity);
			new_mask.add_components<ComponentType>(); 
			systems->react_on_event(entity, new_mask);
		}(),...);
	}

	template<class... ComponentType>
	void remove_components(const Entity& entity) {
		ComponentMask old_mask = entities->get_mask(entity);
		( [&] {
			    components->remove_component<ComponentType>(entity);
			    entities->remove_component_from_entity_mask<ComponentType>(entity);
		    }(), ...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	std::unique_ptr<Entities> entities = std::make_unique<Entities>(this);
	std::unique_ptr<Systems> systems = std::make_unique<Systems>(this);
	std::unique_ptr<Components> components = std::make_unique<Components>(this);
	std::unique_ptr<World> world = std::make_unique<World>(this);

	GameWindow* m_window;
};


#endif
