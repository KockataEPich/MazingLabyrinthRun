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
		entity.add_component(std::make_unique<ActionTypeComponent>())
		    .add_component(std::make_unique<SpeedComponent>())
		    .add_component(std::make_unique<FacingSideComponent>())
		    .add_component(std::make_unique<SkinComponent>())
		    .add_component(std::make_unique<AnimationPlayerComponent>());
	};
};

#endif