#ifndef MOVE_SYSTEM_HEADER
#define MOVE_SYSTEM_HEADER

#include "../../components/ai_component.h"
#include "../../components/facing_side_component.h"
#include "../../components/speed_component.h"
#include "../../components/transform_component.h"
#include "../../world/world.h"
#include "../system.h"

class AI : public System {
public:
	AI() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpeedComponent>();
		m_signature.add_component<FacingSideComponent>();
		m_signature.add_component<AIComponent>();
	}
	void update(float dt) override;
	float const tick_frequency() override { return 5.0f; }
};

#endif