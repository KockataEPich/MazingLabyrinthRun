#ifndef DRAWABLE_ENTITY_COMPONENT_ADDER
#define DRAWABLE_ENTITY_COMPONENT_ADDER

#include "../component_adder.h"

class DrawableAdder : public ComponentAdder {
public:
	void attach_components(EntityHandle& entity) override {
		entity.add_component(std::make_unique<SpriteComponent>()).add_component(std::make_unique<TransformComponent>());
	};
};

#endif