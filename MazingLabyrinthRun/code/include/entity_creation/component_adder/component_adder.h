#ifndef COMPONENT_ADDER_HEADER
#define COMPONENT_ADDER_HEADER

#include "../../entity_base/entity_handle.h"
class ComponentAdder {
public:
	virtual void attach_components(EntityHandle& entity) {};
};
#endif