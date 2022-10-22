#ifndef FACING_SIDE_COMPONENT_HEADER
#define FACING_SIDE_COMPONENT_HEADER

#include "../attribute/facingSide.h"

struct FacingSideComponent : public Component<FacingSideComponent> {
	explicit FacingSideComponent(FacingSide&& side) : m_side{std::move(side)} {};
	FacingSideComponent() = default;
	FacingSide m_side = FacingSide::down;
};

#endif