// ################## THIS FILE IS GENERATED ##################
#ifndef TRANSFORM_SYSTEM_HEADER
#define TRANSFORM_SYSTEM_HEADER

#include <world/world.h>

#include <generated/components/data_components/transform_component.h>
#include <generated/components/data_components/sprite_component.h>

class TransformSystem : public ProducerSystem {
public:
	TransformSystem() {
		m_signature
			.add_component<TransformComponent>()
			.add_component<SpriteComponent>();
	}
	void update() override {
		for (auto& entity : m_registered_entities) {
			ComponentHandle<TransformComponent> transform;
			ComponentHandle<SpriteComponent> sprite;
			m_parent_world->unpack(entity,
				transform,
				sprite);

			for_every_entry(Entity entity,
				*transform,
				*sprite);
		}
	}
private:

	void for_every_entity(Entity entity,
		TransformComponent& transform,
		SpriteComponent& sprite);

};
#endif