#ifndef ENTITIES_HEADER
#define ENTITIES_HEADER

#include <component_base/component_mask.h>
#include <entity_base/entity_manager.h>

#include <map>
#include <memory>

class Game;
class Entities {
public:
	explicit Entities(Game* game) : m_game{game} {}

	void init(){};
	Entity birth_entity() { return m_entity_manager->create_entity(); } 
	ComponentMask get_mask(const Entity entity) { return m_entity_masks[entity]; }
	
	void delete_entity(const Entity entity);

	template<typename ComponentType>
	void add_component_to_entity_mask(const Entity entity) { 
		m_entity_masks[entity].add_components<ComponentType>(); 
	}
	
	template<typename ComponentType>
	void remove_component_from_entity_mask(const Entity entity) {
		m_entity_masks[entity].remove_components<ComponentType>();	
	}

    template<typename ComponentType>
	const std::vector<Entity> get_all_entities_who_have_component() {
		std::vector<Entity> entity_vector;
		ComponentMask component_mask;
		component_mask.add_components<ComponentType>();
		for (auto& [entity, mask] : m_entity_masks)
			if (mask.matches(component_mask)) entity_vector.push_back(entity);
		return entity_vector;
	}

private:
	std::unique_ptr<EntityManager> m_entity_manager = std::make_unique<EntityManager>();
	std::map<Entity, ComponentMask> m_entity_masks;

	Game* m_game;
};

#endif