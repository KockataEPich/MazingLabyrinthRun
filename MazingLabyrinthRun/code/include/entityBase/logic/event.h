#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <SFML/Graphics/Sprite.hpp>
#include <list>
#include <memory>

class Event {
public:
	Event(sf::Sprite* sprite) : m_sprite{sprite} {}
	void apply() {
		before_event();
		event();
		after_event();
	}
	virtual void event() = 0;

	virtual void before_event(){};
	virtual void after_event(){};

	bool is_finished() { return m_finished; }
	virtual int event_recurrence_number() { return m_event_recurrence_number; }

protected:
	sf::Sprite* m_sprite;
	bool m_finished = false;
	int m_event_recurrence_number = 1;
};

template<typename T>
class EventUsingState : public Event {
public:
	EventUsingState(sf::Sprite* sprite, T* state) : Event(sprite), m_state{state} {};

protected:
	T* m_state;
};

class CompositeEvent : public Event {
public:
	void add_event(std::unique_ptr<Event>&& action) { m_events.push_back(std::move(action)); }

protected:
	std::list<std::unique_ptr<Event>> m_events;
};

class ParallelEvent : public CompositeEvent {
public:
	void event() override {
		for (auto& event : m_events) event->apply();
		m_events.remove_if([](std::unique_ptr<Event>& event) { return event->is_finished(); });
		m_finished = m_events.empty();
	}
};

class SequenceEvent : CompositeEvent {
public:
	void event() override {
		if (m_finished = m_events.empty(); m_finished) return;

		m_events.front()->apply();
		if (m_events.front()->is_finished()) m_events.pop_front();
	}
};

#endif