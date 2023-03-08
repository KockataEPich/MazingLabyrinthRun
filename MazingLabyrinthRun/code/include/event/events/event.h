#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <memory>
#include <optional>
#include <utils/vector_utils.h>
#include <vector>

class Event {
public:
	Event(std::optional<int> event_recurrence_number) : m_event_recurrence_number{event_recurrence_number} {}
	Event() = default;

	void happen() {
		before_event();
		apply();
		after_event();

		if (!m_event_recurrence_number.has_value()) return;

		m_event_recurrence_number.value()--;
		if (m_event_recurrence_number == 0) m_finished = true;
	}

	bool is_finished() { return m_finished; }
	std::optional<int> event_recurrence_number() { return m_event_recurrence_number; }

protected:
	bool m_finished = false;
	std::optional<int> m_event_recurrence_number = 1;
	virtual void apply() = 0;

	// Hooks supporting abstraction at lower levels
	virtual void before_event(){};
	virtual void after_event(){};
};

class CompositeEvent : public Event {
public:
	void add_event(std::unique_ptr<Event>&& action) { m_events.push_back(std::move(action)); }

protected:
	std::vector<std::unique_ptr<Event>> m_events;
};

class ParallelEvent : public CompositeEvent {
protected:
	void apply() override {
		for (int i = 0; i < m_events.size(); i++) {
			m_events[i]->happen();
			if (m_events[i]->is_finished()) vec_utils::pop_at_index(i, m_events);
		}

		m_finished = m_events.empty();
	}
};

class SequenceEvent : CompositeEvent {
protected:
	void apply() override {
		if (m_finished = m_events.empty(); m_finished) return;

		m_events.front()->happen();
		if (m_events.front()->is_finished()) vec_utils::pop_front(m_events);
	}
};

#endif
