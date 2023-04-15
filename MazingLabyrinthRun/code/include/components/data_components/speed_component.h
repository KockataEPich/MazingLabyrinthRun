#ifndef SPEED_COMPONENT_HEADER
#define SPEED_COMPONENT_HEADER

#include <component_base/component.h>
struct SpeedComponent : public Component<SpeedComponent> {
	SpeedComponent() = default;
	SpeedComponent(float speed) : m_speed{speed} {};
	float m_speed;
};

#endif