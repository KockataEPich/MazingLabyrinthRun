#ifndef GAME_HEADER
#define GAME_HEADER

#include <window/game_window.h>
#include <generated/components/data_components/boundary_component.h>
#include <generated/components/basic_components/update_boundary_from_transform_component.h>
#include <entity_base/entities.h>
#include <system/systems.h>
#include <component_base/components.h>
#include <world/world.h>
#include <world/quad_tree.h>

struct EntityHandle;
class Game {
public:
	Game(GameWindow* window) : m_window{window} {}

	void init() { 
		entities->init();
		systems->init();
		components->init();
		world->init();
		quad_tree->init();
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
		( [&] { add_component<ComponentType>(entity); }(), ...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	template<class... ComponentType>
	void add_components(const Entity& entity, std::unique_ptr<ComponentType>&&... component) {
		ComponentMask old_mask = entities->get_mask(entity);
		( [&] { add_component(entity, std::move(component)); }(), ...);
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
			    remove_component<ComponentType>(entity);
		 }(), ...);
		systems->update_entity_system_subscriptions(entity, old_mask);
	}

	std::unique_ptr<Entities> entities = std::make_unique<Entities>(this);
	std::unique_ptr<Systems> systems = std::make_unique<Systems>(this);
	std::unique_ptr<Components> components = std::make_unique<Components>(this);
	std::unique_ptr<World> world = std::make_unique<World>(this);
	

	GameWindow* m_window;
	std::unique_ptr<QuadTree> quad_tree = std::make_unique<QuadTree>(this, sf::FloatRect(-4800, -2700, m_window->get_window_size().x * 5, m_window->get_window_size().y * 5), 0);

private:
	template <class ComponentType>
	void add_component(const Entity& entity, std::unique_ptr<ComponentType>&& component) {
		components->add_component(entity, std::move(component));
		entities->add_component_to_entity_mask<ComponentType>(entity);
	}

	template<class ComponentType>
	void add_component(const Entity& entity) {
		components->add_component(entity, std::make_unique<ComponentType>());
		entities->add_component_to_entity_mask<ComponentType>(entity);
	}

	template<>
	void add_component<BoundaryComponent>(const Entity& entity) {
		components->add_component(entity, std::make_unique<BoundaryComponent>());
		entities->add_component_to_entity_mask<BoundaryComponent>(entity);
		add_event_components<UpdateBoundaryFromTransformComponent>(entity);
		quad_tree->insert(entity);
	}

	template<class ComponentType>
	void remove_component(const Entity& entity) {
		components->remove_component<ComponentType>(entity);
		entities->remove_component_from_entity_mask<ComponentType>(entity);
	}

	template<>
	void remove_component<BoundaryComponent>(const Entity& entity) {
		components->remove_component<BoundaryComponent>(entity);
		entities->remove_component_from_entity_mask<BoundaryComponent>(entity);
		quad_tree->remove(entity);
	}

};


#endif
