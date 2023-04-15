#ifndef MOVE_SYSTEM_HEADER
#define MOVE_SYSTEM_HEADER

#include <components/data_components/facing_side_component.h>
#include <components/data_components/speed_component.h>
#include <components/data_components/transform_component.h>
#include <components/event_components/move_event_component.h>
#include <world/world.h>
#include <system/system.h>
class Move : public ReactSystem {
public:
	Move() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpeedComponent>();
		m_signature.add_component<FacingSideComponent>();
		m_signature.add_component<MoveEventComponent>();
	}
	virtual void react(Entity const& entity);
};

#endif