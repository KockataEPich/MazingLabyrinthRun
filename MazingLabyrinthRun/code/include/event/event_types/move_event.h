#ifndef MOVE_EVENT_HEADER
#define MOVE_EVENT_HEADER

#include <entity_base/entity.h>
#include <event/event.h>

struct MoveEvent : public Event {
	MoveEvent(Entity entity) : entity{entity} {}
	Entity entity;
};

#endif