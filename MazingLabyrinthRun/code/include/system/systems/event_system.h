#ifndef EVENT_SYSTEM_HEADER
#define EVENT_SYSTEM_HEADER

#include "../../components/status_list_component.h"
#include "../../world/world.h"
#include "../system.h"

class EventSystem : public System {
public:
	EventSystem() { m_signature.add_component<StatusListComponent>(); }
	void update(float dt) override;
};

#endif