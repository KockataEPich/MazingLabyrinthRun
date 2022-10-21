#ifndef FACING_SIDE_COMPONENT_HEADER
#define FACING_SIDE_COMPONENT_HEADER

#include "../attribute/facingSide.h"

struct FacingSideComponent : public Component<FacingSideComponent> {
	FacingSide m_side = FacingSide::down;
};

#endif