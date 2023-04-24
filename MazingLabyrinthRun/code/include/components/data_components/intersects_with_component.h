#ifndef INTERSECTS_LIST_COMPONENT_HEADER
#define INTERSECTS_LIST_COMPONENT_HEADER

#include <component_base/component.h>

#include <entity_base/entity.h>

struct IntersectsWith : public Component<IntersectsWith> {
	IntersectsWith() = default;
	Entity m_entity;
};


#endif