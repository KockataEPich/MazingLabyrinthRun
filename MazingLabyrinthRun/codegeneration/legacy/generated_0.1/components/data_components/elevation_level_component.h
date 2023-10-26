// ################## THIS FILE IS GENERATED ##################
#ifndef ELEVATION_LEVEL_COMPONENT_HEADER
#define ELEVATION_LEVEL_COMPONENT_HEADER

#include <component_base/component.h>
#include <attribute/elevation_level.h>

struct ElevationLevelComponent : public Component<ElevationLevelComponent> {
	ElevationLevelComponent() = default;
	explicit ElevationLevelComponent(
		ElevationLevel&& level) : 
		m_level{level}{};

	ElevationLevel m_level = ElevationLevel::two;
};
#endif