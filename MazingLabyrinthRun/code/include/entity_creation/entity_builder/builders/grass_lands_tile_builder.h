#ifndef GRASS_TILE_ENTITY_BUILDER_BASE_HEADER
#define GRASS_TILE_ENTITY_BUILDER_BASE_HEADER

#include "../../component_adder/adders/drawable_adder.h"
#include "../../component_initializer/initializers/basic_drawable_initializer.h"
#include "../entity_builder.h"
class GrassLandsTileBuilder : public EntityBuilder<1, 1> {
public:
	GrassLandsTileBuilder() {
		m_component_adders = {std::make_unique<DrawableAdder>()};
		m_component_initializers = {std::make_unique<BasicDrawableInitializer>(Textures::ID::GRASS_LANDS_1)};
	}
};
#endif
