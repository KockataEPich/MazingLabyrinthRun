// ################## THIS FILE IS GENERATED ##################
#ifndef SPEED_COMPONENT_HEADER
#define SPEED_COMPONENT_HEADER

#include <component_base/component.h>

struct SpeedComponent : public Component<SpeedComponent> {
	SpeedComponent() = default;
	explicit SpeedComponent(
		float&& speed) : 
		speed{speed}{}

	float speed;
};
#endif