#ifndef AI_COMPONENT_ADDER
#define AI_COMPONENT_ADDER

#include "../component_adder.h"
#include <generated/components/basic_components/ai_component.h>
class AIAdder : public ComponentAdder {
public:
	void attach_components(EntityHandle& entity) override {
		entity.add_components(std::make_unique<AIComponent>());
	};
};

#endif