#ifndef ZOMBIE_ENTITY_BUILDER_BASE_HEADER
#define ZOMBIE_ENTITY_BUILDER_BASE_HEADER

#include "../../component_adder/adders/animated_adder.h"
#include "../../component_adder/adders/drawable_adder.h"
#include "../../component_initializer/initializers/animated_drawable_initializer.h"
#include "../entity_builder.h"

class ZombieEntityBuilder : public EntityBuilder<2, 1> {
private:
	std::array<std::unique_ptr<ComponentAdder>, 2> get_adders() override {
		return {std::make_unique<DrawableAdder>(), std::make_unique<AnimatedAdder>()};
	};
	std::array<std::unique_ptr<ComponentInitializer>, 1> get_initializers() override {
		return {std::make_unique<AnimatedDrawableInitializer>(Skin::ZOMBIE_DEFAULT_SKIN, 100.0f)};
	};
};
#endif
