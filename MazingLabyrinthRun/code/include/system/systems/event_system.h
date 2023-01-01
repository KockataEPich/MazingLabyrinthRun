#ifndef EVENT_SYSTEM_HEADER
#define EVENT_SYSTEM_HEADER

#include "../../components/composite_event_component.h"
#include "../../world/world.h"
#include "../system.h"

class EventSystem : public System {
public:
	EventSystem() { m_signature.add_component<CompositeEventComponent>(); }
	void update(float dt) override;
};

#endif