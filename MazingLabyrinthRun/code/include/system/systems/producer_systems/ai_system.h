#ifndef AI_SYSTEM_HEADER
#define AI_SYSTEM_HEADER

#include <components/data_components/ai_component.h>
#include <components/data_components/facing_side_component.h>
#include <components/data_components/speed_component.h>
#include <components/data_components/transform_component.h>
#include <world/world.h>
#include <system/system.h>

class AI : public ProducerSystem {
public:
	AI() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SpeedComponent>();
		m_signature.add_component<FacingSideComponent>();
		m_signature.add_component<AIComponent>();
	}
	void update() override;
	int const tick_frequency() override { return 5; }
};

#endif