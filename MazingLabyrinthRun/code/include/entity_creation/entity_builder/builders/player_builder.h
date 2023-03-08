#ifndef PLAYER_ENTITY_BUILDER_BASE_HEADER
#define PLAYER_ENTITY_BUILDER_BASE_HEADER

#include "../../component_adder/adders/animated_adder.h"
#include "../../component_adder/adders/drawable_adder.h"
#include "../../component_adder/adders/player_adder.h"
#include "../../component_initializer/initializers/animated_drawable_initializer.h"
#include "../entity_builder.h"

class PlayerEntityBuilder : public EntityBuilder<3, 1> {
public:
	PlayerEntityBuilder() {
		m_component_adders = {std::make_unique<DrawableAdder>(ElevationLevel::two),
		                      std::make_unique<AnimatedAdder>(),
		                      std::make_unique<PlayerAdder>()};

		m_component_initializers = {
		    std::make_unique<AnimatedDrawableInitializer>(Skin::MAIN_CHARACTER_START_SKIN, 10.0f)};
	}
};
#endif
