// ################## THIS FILE IS GENERATED ##################
#ifndef FACING_SIDE_COMPONENT_HEADER
#define FACING_SIDE_COMPONENT_HEADER

#include <component_base/component.h>
#include <attribute/facing_side.h>

struct FacingSideComponent : public Component<FacingSideComponent> {
	FacingSideComponent() = default;
	explicit FacingSideComponent(
		FacingSide&& side) : 
		side{side}{}

	FacingSide side = FacingSide::left;
};
#endif