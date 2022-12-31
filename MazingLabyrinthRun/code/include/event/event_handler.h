#ifndef EVENT_HANDLER_HEADER
#define EVENT_HANDLER_HEADER

#include <entity_base/entity.h>
#include <event/events/event.h>
#include <unordered_map>

class World;
class EventHandler {
public:
	EventHandler(World* world) : m_world{world} {}
	add_event_to_entity(Entity entity, Event&& event) {}

private:
	std::unordered_map<Entity, std::vector<Event>> m_entity_event_map;
	World* m_world;
};

#endif
