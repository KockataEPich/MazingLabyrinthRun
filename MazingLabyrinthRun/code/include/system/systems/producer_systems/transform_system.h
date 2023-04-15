#ifndef TRANSFORM_SYSTEM_HEADER
#define TRANSFORM_SYSTEM_HEADER

#include <components/data_components/sprite_component.h>
#include <components/data_components/transform_component.h>
#include <world/world.h>
#include <system/system.h>

class Transform : public ProducerSystem {
public:
	Transform() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpriteComponent>();
	}
	void update() override;
};

#endif