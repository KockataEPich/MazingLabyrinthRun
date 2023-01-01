#ifndef AI_COMPONENT_ADDER
#define AI_COMPONENT_ADDER

#include "../component_adder.h"
#include <components/ai_component.h>
class AIAdder : public ComponentAdder {
public:
	void attach_components(EntityHandle& entity) override {
		entity.add_component(std::make_unique<AIComponent>());
	};
};

#endif