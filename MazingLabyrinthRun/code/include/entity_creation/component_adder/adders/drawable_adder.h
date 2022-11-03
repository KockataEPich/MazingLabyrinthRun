#ifndef DRAWABLE_ENTITY_COMPONENT_ADDER
#define DRAWABLE_ENTITY_COMPONENT_ADDER

#include "../component_adder.h"

#include <components/elevation_component.h>
#include <components/sprite_component.h>
#include <components/transform_component.h>

class DrawableAdder : public ComponentAdder {
public:
	DrawableAdder(ElevationLevel level) : m_level{level} {};
	void attach_components(EntityHandle& entity) override {
		entity.add_component(std::make_unique<SpriteComponent>())
		    .add_component(std::make_unique<TransformComponent>())
		    .add_component(std::make_unique<ElevationLevelComponent>(m_level));
	};

private:
	ElevationLevel m_level;
};

#endif