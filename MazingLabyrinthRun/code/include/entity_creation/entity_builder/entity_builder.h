#ifndef ENTITY_BUILDER_BASE_HEADER
#define ENTITY_BUILDER_BASE_HEADER

#include "../../entity_base/entity_handle.h"
#include "../component_adder/component_adder.h"
#include "../component_initializer/component_initializer.h"

template<unsigned int N, unsigned int M>
class EntityBuilder {
public:
	void build_entity(EntityHandle& entity) {
		for (auto& component_adder : get_adders()) component_adder->attach_components(entity);
		for (auto& component_initializer : get_initializers()) component_initializer->initialize_components(entity);
	};

	virtual std::array<std::unique_ptr<ComponentAdder>, N> get_adders() = 0;
	virtual std::array<std::unique_ptr<ComponentInitializer>, M> get_initializers() = 0;
};
#endif