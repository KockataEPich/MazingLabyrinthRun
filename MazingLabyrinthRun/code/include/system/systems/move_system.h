#ifndef MOVE_SYSTEM_HEADER
#define MOVE_SYSTEM_HEADER

#include "../../components/facing_side_component.h"
#include "../../components/move_component.h"
#include "../../components/transform_component.h"
#include "../../world/world.h"
#include "../system.h"

class Move : public System {
public:
	Move() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<MoveComponent>();
		m_signature.add_component<FacingSideComponent>();
	}
	void update(float dt) override;
};

#endif