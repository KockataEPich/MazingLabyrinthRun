#ifndef COMPOSITE_EVENT_COMPONENT_HEADER
#define COMPOSITE_EVENT_COMPONENT_HEADER

#include "../component_base/component.h"

#include <event/events/event.h>
#include <vector>

struct StatusListComponent : public Component<StatusListComponent> {
	explicit StatusListComponent(std::unique_ptr<ParallelEvent>&& events) : m_events{std::move(events)} {}
	StatusListComponent() = default;
	std::unique_ptr<ParallelEvent> m_events = std::make_unique<ParallelEvent>();
};

#endif