#ifndef GRASS_TILE_ENTITY_BUILDER_BASE_HEADER
#define GRASS_TILE_ENTITY_BUILDER_BASE_HEADER

#include "../../component_adder/adders/drawable_adder.h"
#include "../../component_initializer/initializers/basic_drawable_initializer.h"
#include "../entity_builder.h"

const int N = 1;
const int M = 1;
class GrassLandsTileBuilder : public EntityBuilder<N, M> {
private:
	std::array<std::unique_ptr<ComponentAdder>, N> get_adders() override {
		return {std::make_unique<DrawableAdder>()};
	};
	std::array<std::unique_ptr<ComponentInitializer>, M> get_initializers() override {
		return {std::make_unique<BasicDrawableInitializer>(Textures::ID::GRASS_LANDS_1)};
	};
};
#endif
