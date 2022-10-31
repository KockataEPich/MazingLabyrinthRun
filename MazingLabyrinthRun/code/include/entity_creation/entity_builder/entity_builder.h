#ifndef ENTITY_BUILDER_BASE_HEADER
#define ENTITY_BUILDER_BASE_HEADER

#include "../../entity_base/entity_handle.h"
#include "../component_adder/component_adder.h"
#include "../component_initializer/component_initializer.h"

template<unsigned int AddersLength, unsigned int InitializerLength>
class EntityBuilder {
public:
	void build_entity(EntityHandle& entity) {
		assert(!m_component_adders.empty() || !m_component_initializers.empty());
		for (auto& adder : m_component_adders) adder->attach_components(entity);
		for (auto& initializer : m_component_initializers) initializer->initialize_components(entity);
	};

protected:
	std::array<std::unique_ptr<ComponentAdder>, AddersLength> m_component_adders;
	std::array<std::unique_ptr<ComponentInitializer>, InitializerLength> m_component_initializers;
};
#endif