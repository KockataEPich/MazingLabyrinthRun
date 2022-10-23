#ifndef MOVE_COMPONENT_HEADER
#define MOVE_COMPONENT_HEADER

#include "../component_base/component.h"
struct SpeedComponent : public Component<SpeedComponent> {
	SpeedComponent(float speed) : m_speed{speed} {};
	float m_speed;
};

#endif