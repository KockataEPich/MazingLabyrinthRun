#ifndef MOVE_EVENT_HEADER
#define MOVE_EVENT_HEADER

#include "../event.h"

#include <attribute/facingSide.h>
#include <components/transform_component.h>

class RunEvent : public Event {
public:
	RunEvent(TransformComponent& transform, SpeedComponent& speed, FacingSideComponent& side)
	    : m_transform{transform}
	    , m_speed{speed}
	    , m_side{side} {}

protected:
	TransformComponent& m_transform;
	SpeedComponent& m_speed;
	FacingSideComponent& m_side;
};

class RunRight : public RunEvent {
public:
	RunRight(TransformComponent& transform, SpeedComponent& speed, FacingSideComponent& side)
	    : RunEvent(transform, speed, side){};
private:
	void apply() override {
		m_transform.m_position = {m_transform.m_position.x + m_speed.m_speed, m_transform.m_position.y};
		m_side.m_side = FacingSide::right;
	};
};

class RunLeft : public RunEvent {
public:
	RunLeft(TransformComponent& transform, SpeedComponent& speed, FacingSideComponent& side)
	    : RunEvent(transform, speed, side){};

private:
	void apply() override {
		m_transform.m_position = {m_transform.m_position.x - m_speed.m_speed, m_transform.m_position.y};
		m_side.m_side = FacingSide::left;
	};
};

class RunUp : public RunEvent {
public:
	RunUp(TransformComponent& transform, SpeedComponent& speed, FacingSideComponent& side)
	    : RunEvent(transform, speed, side){};

private:
	void apply() override {
		m_transform.m_position = {m_transform.m_position.x, m_transform.m_position.y - m_speed.m_speed};
		m_side.m_side = FacingSide::up;
	};
};

class RunDown : public RunEvent {
public:
	RunDown(TransformComponent& transform, SpeedComponent& speed, FacingSideComponent& side)
	    : RunEvent(transform, speed, side){};

private:
	void apply() override {
		m_transform.m_position = {m_transform.m_position.x , m_transform.m_position.y + m_speed.m_speed};
		m_side.m_side = FacingSide::down;
	};
};
#endif