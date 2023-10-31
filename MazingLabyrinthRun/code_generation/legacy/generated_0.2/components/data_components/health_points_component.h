// ################## THIS FILE IS GENERATED ##################
#ifndef HEALTH_POINTS_COMPONENT_HEADER
#define HEALTH_POINTS_COMPONENT_HEADER

#include <component_base/component.h>
#include <attribute/elevation_level.h>

struct HealthPointsComponent : public Component<HealthPointsComponent> {
	HealthPointsComponent() = default;
	explicit HealthPointsComponent(
		int&& health) : 
		health{health}{}

	int health = 50;
};
#endif