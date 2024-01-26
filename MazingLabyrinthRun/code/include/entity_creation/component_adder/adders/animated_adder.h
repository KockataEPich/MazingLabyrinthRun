#ifndef ANIMATED_ENTITY_COMPONENT_ADDER
#define ANIMATED_ENTITY_COMPONENT_ADDER

#include "../component_adder.h"

#include <generated/components/data_components/action_type_component.h>
#include <generated/components/data_components/animation_player_component.h>
#include <generated/components/data_components/facing_side_component.h>
#include <generated/components/data_components/skin_component.h>
#include <generated/components/data_components/speed_component.h>

class AnimatedAdder : public ComponentAdder {
public:
	void attach_components(EntityHandle& entity) override {
		entity.add_components(std::make_unique<ActionTypeComponent>(),
			std::make_unique<SpeedComponent>(),
			std::make_unique<FacingSideComponent>(),
			std::make_unique<SkinComponent>(),
			std::make_unique<AnimationPlayerComponent>());
	};
};

#endif