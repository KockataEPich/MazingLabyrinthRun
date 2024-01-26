#ifndef PLAYER_ENTITY_COMPONENT_ADDER
#define PLAYER_ENTITY_COMPONENT_ADDER

#include "../component_adder.h"
#include <generated/components/basic_components/player_component.h>
class PlayerAdder : public ComponentAdder {
public:
	void attach_components(EntityHandle& entity) override {
		entity.add_components(std::make_unique<PlayerComponent>());
	};
};

#endif