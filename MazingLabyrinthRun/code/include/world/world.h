#ifndef WORLD_HEADER_H
#define WORLD_HEADER_H

#include "../component_base/component_handle.h"
#include "../component_base/component_manager.h"
#include "../entity_base/entity_manager.h"
#include "../entity_creation/entity_list.h"
#include "../system/system.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <any>
#include <memory>

struct EntityHandle;
class World {
public:
	explicit World(std::unique_ptr<EntityManager> entityManager);

	void init();

	void update(float dt);
	void render();
	EntityHandle create_entity();
	World* add_system(std::unique_ptr<System> system);
	void add_render_system(std::unique_ptr<System> system);
	void destroy_entity(Entity entity);
	bool place_entity(EntityHandle& handle, sf::Vector2f position);

	template<typename ComponentType>
	void add_custom_component_manager(std::unique_ptr<ComponentManager<ComponentType>> manager) {
		int family = GetComponentFamily<ComponentType>();
		if (family >= m_component_managers.size()) { m_component_managers.resize(family + 1); }
		m_component_managers[family] = manager;
	}

	template<typename ComponentType>
	void add_component(Entity const& entity, std::unique_ptr<ComponentType>&& component) {
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		manager->add_component(entity, std::move(component));

		ComponentMask oldMask = m_entity_masks[entity];
		m_entity_masks[entity].add_component<ComponentType>();

		update_entity_mask(entity, oldMask);
	}

	template<typename ComponentType>
	void remove_component(Entity const& entity) {
		ComponentManager<ComponentType>* manager = get_component_manager<ComponentType>();
		ComponentHandle<ComponentType> component = manager->lookup(entity);
		component.destroy();

		ComponentMask oldMask = m_entity_masks[entity];
		m_entity_masks[entity].remove_component<ComponentType>();

		update_entity_mask(entity, oldMask);
	}

	template<typename ComponentType, typename... Args>
	void unpack(Entity e, ComponentHandle<ComponentType>& handle, ComponentHandle<Args>&... args) {
		unpack(e, handle);
		unpack<Args...>(e, args...);
	}

	// Base case
	template<typename ComponentType>
	void unpack(Entity e, ComponentHandle<ComponentType>& handle) {
		typedef ComponentManager<ComponentType> ComponentManagerType;
		auto manger = get_component_manager<ComponentType>();
		handle = ComponentHandle<ComponentType>(e, manger->lookup(e), manger);
	}

	void set_player_location(sf::Sprite* player_sprite) { m_player_sprite = player_sprite; }
	sf::Vector2f get_player_location() { return m_player_sprite->getPosition(); }

private:
	std::unique_ptr<EntityManager> m_entity_manager;
	std::vector<std::unique_ptr<System>> m_systems;
	std::vector<std::unique_ptr<System>> m_render_systems;
	std::vector<std::unique_ptr<BaseComponentManager>> m_component_managers;
	std::map<Entity, ComponentMask> m_entity_masks;
	sf::Sprite* m_player_sprite;

	void update_entity_mask(Entity const& entity, ComponentMask old_mask);

	template<typename ComponentType>
	ComponentManager<ComponentType>* get_component_manager() {
		int family = get_component_family<ComponentType>();

		if (family >= m_component_managers.size()) { m_component_managers.resize(family + 1); }

		if (!m_component_managers[family]) {
			m_component_managers[family] = std::make_unique<ComponentManager<ComponentType>>();
		}

		return static_cast<ComponentManager<ComponentType>*>(m_component_managers[family].get());
	}
};
#endif