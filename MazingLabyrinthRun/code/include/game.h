#ifndef GAME_HEADER
#define GAME_HEADER

#include <window/game_window.h>
#include <generated/components/data_components/boundary_component.h>
#include <generated/events/update_boundary_from_transform_event.h>

#include <entity_base/entities.h>
#include <system/systems.h>
#include <component_base/components.h>
#include <world/world.h>
#include <world/quad_tree.h>
#include <ui/ui_manager.h>
#include <event/event_bus.h>

#include <time/time_manager.h>

struct EntityHandle;
class Game {
public:
	Game(GameWindow* window) : window{window} {}

	void init() { 
		entities->init();
		systems->init();
		components->init();
		world->init();
		quad_tree->init();
		ui_manager->init();
	}

	EntityHandle create_entity();

	void destroy_entity(const Entity entity) {
		quad_tree->remove(entity);
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
			    if constexpr (std::is_same_v<ComponentType, BoundaryComponent>) {
				    event_bus->publish(entity, UpdateBoundaryFromTransformEvent());
				    quad_tree->insert(entity);
			    }
			}(), ...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	template<class... ComponentType>
	void add_components(const Entity& entity, std::unique_ptr<ComponentType>&&... component) {
		ComponentMask old_mask = entities->get_mask(entity);
		( [&] {
			    components->add_component(entity, std::move(component));
			    entities->add_component_to_entity_mask<ComponentType>(entity);
	    }(),...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	template<class... ComponentType>
	void remove_components(const Entity& entity) {
		ComponentMask old_mask = entities->get_mask(entity);
		( [&] {
			    components->remove_component<ComponentType>(entity);
			    entities->remove_component_from_entity_mask<ComponentType>(entity);
			    if constexpr (std::is_same_v<ComponentType, BoundaryComponent>) { quad_tree->remove(entity);}
		 }(), ...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}
	
	void update(float dt) { 
		TimeManager::get_instance()->update_tracks(dt);
		systems->update(dt);
	}

	void render() { 
		systems->render();
		ui_manager->render_ui();
	}

	void update_ui();

	std::unique_ptr<Entities> entities = std::make_unique<Entities>(this);
	std::unique_ptr<Systems> systems = std::make_unique<Systems>(this);
	std::unique_ptr<Components> components = std::make_unique<Components>(this);
	std::unique_ptr<World> world = std::make_unique<World>(this);
	std::unique_ptr<UIManager> ui_manager = std::make_unique<UIManager>(this);
	std::unique_ptr<EventBus> event_bus = std::make_unique<EventBus>();

	GameWindow* window;
	std::unique_ptr<QuadTree> quad_tree = std::make_unique<QuadTree>(
		this, 
		sf::FloatRect(-4800, -2700, window->get_window_size().x * 5,
		window->get_window_size().y * 5), 
		0);

	Entity mouse;
	Entity player;
};


#endif
