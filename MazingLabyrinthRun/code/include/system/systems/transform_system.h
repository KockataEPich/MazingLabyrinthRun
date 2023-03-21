#ifndef TRANSFORM_SYSTEM_HEADER
#define TRANSFORM_SYSTEM_HEADER

#include "../../components/sprite_component.h"
#include "../../components/transform_component.h"
#include "../../world/world.h"
#include "../system.h"

class Transform : public System {
public:
	Transform() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpriteComponent>();
	}
	void update() override;
};

#endif