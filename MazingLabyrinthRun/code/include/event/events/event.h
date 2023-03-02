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

	void happen(float dt) {
		before_event(dt);
		apply(dt);
		after_event(dt);

		if (!m_event_recurrence_number.has_value()) return;

		m_event_recurrence_number.value()--;
		if (m_event_recurrence_number == 0) m_finished = true;
	}

	// Hooks supporting abstraction at lower levels
	virtual void before_event(float dt){};
	virtual void after_event(float dt){};

	bool is_finished() { return m_finished; }
	std::optional<int> event_recurrence_number() { return m_event_recurrence_number; }

protected:
	bool m_finished = false;
	std::optional<int> m_event_recurrence_number = 1;
	virtual void apply(float dt) = 0;
};

class CompositeEvent : public Event {
public:
	void add_event(std::unique_ptr<Event>&& action) { m_events.push_back(std::move(action)); }

protected:
	std::vector<std::unique_ptr<Event>> m_events;
};

class ParallelEvent : public CompositeEvent {
protected:
	void apply(float dt) override {
		for (int i = 0; i < m_events.size(); i++) {
			m_events[i]->happen(dt);
			if (m_events[i]->is_finished()) vec_utils::pop_at_index(i, m_events);
		}

		m_finished = m_events.empty();
	}
};

class SequenceEvent : CompositeEvent {
protected:
	void apply(float dt) override {
		if (m_finished = m_events.empty(); m_finished) return;

		m_events.front()->happen(dt);
		if (m_events.front()->is_finished()) vec_utils::pop_front(m_events);
	}
};

#endif
