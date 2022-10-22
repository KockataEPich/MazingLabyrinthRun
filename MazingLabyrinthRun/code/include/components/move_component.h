#ifndef MOVE_COMPONENT_HEADER
#define MOVE_COMPONENT_HEADER

#include "../component_base/component.h"
struct MoveComponent : public Component<MoveComponent> {
	MoveComponent(float speed) : m_speed{speed} {};
	float m_speed;
};

#endif