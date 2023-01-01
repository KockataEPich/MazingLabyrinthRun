#ifndef MOVE_SYSTEM_HEADER
#define MOVE_SYSTEM_HEADER

#include "../../components/facing_side_component.h"
#include "../../components/speed_component.h"
#include "../../components/transform_component.h"
#include "../../world/world.h"
#include "../system.h"
#include <components/action_type_component.h>
#include <components/composite_event_component.h>
class Move : public System {
public:
	Move() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpeedComponent>();
		m_signature.add_component<FacingSideComponent>();
		m_signature.add_component<ActionTypeComponent>();
		m_signature.add_component<CompositeEventComponent>();
	}
	void update(float dt) override;
};

#endif