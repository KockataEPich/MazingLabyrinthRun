#ifndef ELEVATION_LEVEL_COMPONENT_HEADER
#define ELEVATION_LEVEL_COMPONENT_HEADER

#include <attribute/elevation_level.h>
#include <component_base/component.h>

struct ElevationLevelComponent : public Component<ElevationLevelComponent> {
	explicit ElevationLevelComponent(ElevationLevel level) : m_level{level} {};
	ElevationLevelComponent() = default;
	ElevationLevel m_level = ElevationLevel::two;
};

#endif