// ################## THIS FILE IS GENERATED ##################
#ifndef COLLISION_DETECTION_SYSTEM_HEADER
#define COLLISION_DETECTION_SYSTEM_HEADER

#include <world/world.h>

#include <generated/components/data_components/boundary_component.h>
#include <generated/components/data_components/transform_component.h>
#include <generated/components/basic_components/collisioncheck_component.h>

class CollisionDetectionSystem : public ReactSystem {
public:
	CollisionDetectionSystem() {
		m_signature
			.add_component<BoundaryComponent>()
			.add_component<TransformComponent>()
			.add_component<CollisionCheckComponent>();
	}
	void react(const Entity& entity) override {
		ComponentHandle<BoundaryComponent> boundary;
		ComponentHandle<TransformComponent> transform;
		m_parent_world->unpack(entity,
			boundary,
			transform);

		react_on_entity(Entity entity,
			*boundary,
			*transform);
	}
private:

	void react_on_entity(Entity entity,
		BoundaryComponent& boundary,
		TransformComponent& transform,
		CollisionCheckComponent& collisioncheck);

};
#endif