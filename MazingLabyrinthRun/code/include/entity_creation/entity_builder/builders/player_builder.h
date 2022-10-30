#ifndef PLAYER_ENTITY_BUILDER_BASE_HEADER
#define PLAYER_ENTITY_BUILDER_BASE_HEADER

#include "../../component_adder/adders/animated_adder.h"
#include "../../component_adder/adders/drawable_adder.h"
#include "../../component_adder/adders/player_adder.h"
#include "../../component_initializer/initializers/animated_drawable_initializer.h"
#include "../entity_builder.h"

class PlayerEntityBuilder : public EntityBuilder<3, 1> {
private:
	std::array<std::unique_ptr<ComponentAdder>, 3> get_adders() override {
		return {std::make_unique<DrawableAdder>(), std::make_unique<AnimatedAdder>(), std::make_unique<PlayerAdder>()};
	};
	std::array<std::unique_ptr<ComponentInitializer>, 1> get_initializers() override {
		return {std::make_unique<AnimatedDrawableInitializer>(Skin::MAIN_CHARACTER_START_SKIN, 200.0f)};
	};
};
#endif
