// ################## THIS FILE IS GENERATED ##################
#ifndef FACING_SIDE_COMPONENT_HEADER
#define FACING_SIDE_COMPONENT_HEADER

#include <component_base/component.h>
#include <attribute/facing_side.h>

struct FacingSideComponent : public Component<FacingSideComponent> {
	FacingSideComponent() = default;
	explicit FacingSideComponent(
		FacingSide&& side) : 
		m_side{side}{};

	FacingSide m_side = FacingSide::left;
};
#endif