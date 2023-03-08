#ifndef EVENT_HANDLER_HEADER
#define EVENT_HANDLER_HEADER

#include <entity_base/entity.h>
#include <event/events/event.h>
#include <world/world.h>

class World;
class EventHandler {
public:
	void execute_event(Entity entity, Event&& event, float dt) { event.happen(dt); }

};

#endif
