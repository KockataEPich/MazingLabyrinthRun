#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <optional>
#include <vector>
#include <utils/vector_utils.h>
#include <memory>

class Event {
public:
	Event(std::optional<int> event_recurrence_number) : m_event_recurrence_number{event_recurrence_number} {}
	Event() = default;

	void happen(float dt) {
		before_event(dt);
		apply(dt);
		after_event(dt);
	}
	virtual void apply(float dt) = 0;

	// Hooks supporting abstraction at lower levels
	virtual void before_event(float dt){};
	virtual void after_event(float dt){};

	bool is_finished() { return m_finished; }
	std::optional<int> event_recurrence_number() { return m_event_recurrence_number; }

protected:
	bool m_finished = false;
	std::optional<int> m_event_recurrence_number = 1;
};

class CompositeEvent : public Event {
public:
	void add_event(std::unique_ptr<Event>&& action) { m_events.push_back(std::move(action)); }

protected:
	std::vector<std::unique_ptr<Event>> m_events;
};

class ParallelEvent : public CompositeEvent {
public:
	void apply(float dt) override {
		for (auto& event : m_events) {
			event->apply(dt);
			if (m_event_recurrence_number.has_value()) m_event_recurrence_number.value()--;
		}
		std::remove_if(m_events.begin(), m_events.end(), [](std::unique_ptr<Event>& event) {
			return event->is_finished();
		});
		m_finished = m_events.empty();
	}
};

class SequenceEvent : CompositeEvent {
public:
	void apply(float dt) override {
		if (m_finished = m_events.empty(); m_finished) return;

		m_events.front()->apply(dt);
		if (m_events.front()->is_finished()) pop_front(m_events);
	}
};

#endif
