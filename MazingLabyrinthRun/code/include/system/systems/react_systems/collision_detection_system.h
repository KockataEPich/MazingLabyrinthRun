#ifndef COLLISION_DETECTION_SYSTEM_HEADER
#define COLLISION_DETECTION_SYSTEM_HEADER

#include <components/data_components/boundary_component.h>
#include <components/data_components/transform_component.h>
#include <components/event_components/check_collision_event_component.h>

#include <world/world.h>
#include <system/system.h>

class CollisionDetection : public ReactSystem {
public:
	CollisionDetection() {
		m_signature.add_component<BoundaryComponent>();
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<CheckCollisionEventComponent>();
	}
	void react(Entity const& entity);
};

#endif