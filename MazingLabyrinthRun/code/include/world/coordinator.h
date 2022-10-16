#ifndef COORDINATOR_HEADER
#define COORDINATOR_HEADER

#include "../components/component_manager.h"
#include "../entity/entity_manager.h"
#include "../systems/system_manager.h"

#include <memory>
class Coordinator {
public:
	void Init() {
		// Create pointers to each manager
		m_component_manager = std::make_unique<ComponentManager>();
		m_entity_manager = std::make_unique<EntityManager>();
		m_system_manager = std::make_unique<SystemManager>();
	}

	// Entity methods
	Entity create_entity() { return m_entity_manager->create_entity(); }

	void destroy_entity(Entity entity) {
		m_entity_manager->destroy_entity(entity);
		m_component_manager->entity_destroyed(entity);
		m_system_manager->entity_destroyed(entity);
	}

	// Component methods
	template<typename T>
	void register_component() {
		m_component_manager->register_component<T>();
	}

	template<typename T>
	void add_component(Entity entity, T component) {
		m_component_manager->add_component<T>(entity, component);

		auto signature = m_entity_manager->get_signature(entity);
		signature.set(m_component_manager->get_component_type<T>(), true);
		m_entity_manager->set_signature(entity, signature);

		m_system_manager->entity_signature_changed(entity, signature);
	}

	template<typename T>
	void remove_component(Entity entity) {
		m_component_manager->remove_component<T>(entity);

		auto signature = m_entity_manager->get_signature(entity);
		signature.set(m_component_manager->get_component_type<T>(), false);
		m_entity_manager->set_signature(entity, signature);

		m_system_manager->entity_signature_changed(entity, signature);
	}

	template<typename T>
	T& get_component(Entity entity) {
		return m_component_manager->get_component<T>(entity);
	}

	template<typename T>
	ComponentType get_component_type() {
		return m_component_manager->get_component_type<T>();
	}

	// System methods
	template<typename T>
	std::shared_ptr<T> register_system() {
		return m_system_manager->register_system<T>();
	}

	template<typename T>
	void set_system_signature(Signature signature) {
		m_system_manager->set_signature<T>(signature);
	}

private:
	std::unique_ptr<ComponentManager> m_component_manager;
	std::unique_ptr<EntityManager> m_entity_manager;
	std::unique_ptr<SystemManager> m_system_manager;
};

#endif