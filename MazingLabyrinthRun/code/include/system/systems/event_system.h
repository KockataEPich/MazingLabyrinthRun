#ifndef EVENT_SYSTEM_HEADER
#define EVENT_SYSTEM_HEADER

#include "../../world/world.h"
#include "../system.h"

class EventSystem : public System {
public:
	EventSystem() { }
	void update() override;
};

#endif