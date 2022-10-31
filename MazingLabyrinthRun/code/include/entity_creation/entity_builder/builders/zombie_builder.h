#ifndef ZOMBIE_ENTITY_BUILDER_BASE_HEADER
#define ZOMBIE_ENTITY_BUILDER_BASE_HEADER

#include "../../component_adder/adders/animated_adder.h"
#include "../../component_adder/adders/drawable_adder.h"
#include "../../component_initializer/initializers/animated_drawable_initializer.h"
#include "../entity_builder.h"

class ZombieEntityBuilder : public EntityBuilder<2, 1> {
public:
	ZombieEntityBuilder() {
		m_component_adders = {std::make_unique<DrawableAdder>(), std::make_unique<AnimatedAdder>()};
		m_component_initializers = {
		    std::make_unique<AnimatedDrawableInitializer>(Skin::ZOMBIE_DEFAULT_SKIN, 200.0f)};
	}
};
#endif
