#ifndef STATUS_LIST_COMPONENT_HEADER
#define STATUS_LIST_COMPONENT_HEADER

#include "../component_base/component.h"

#include <event/events/event.h>
#include <vector>

struct StatusListComponent : public Component<StatusListComponent> {
	explicit StatusListComponent(std::unique_ptr<CompositeEvent>&& status_list)
	    : m_status_list{std::move(status_list)} {}
	StatusListComponent() = default;
	std::unique_ptr<CompositeEvent> m_status_list = {};
};

#endif