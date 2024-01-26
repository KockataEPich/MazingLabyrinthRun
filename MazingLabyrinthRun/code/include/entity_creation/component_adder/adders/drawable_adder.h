#ifndef DRAWABLE_ENTITY_COMPONENT_ADDER
#define DRAWABLE_ENTITY_COMPONENT_ADDER

#include "../component_adder.h"

#include <generated/components/data_components/elevation_level_component.h>
#include <generated/components/data_components/sprite_component.h>
#include <generated/components/data_components/transform_component.h>

class DrawableAdder : public ComponentAdder {
public:
	DrawableAdder(ElevationLevel level) : m_level{level} {};
	void attach_components(EntityHandle& entity) override {
		entity.add_components(
			std::make_unique<SpriteComponent>(),
			std::make_unique<TransformComponent>(),
			std::make_unique<ElevationLevelComponent>(std::move(m_level)));
	};

private:
	ElevationLevel m_level;
};

#endif