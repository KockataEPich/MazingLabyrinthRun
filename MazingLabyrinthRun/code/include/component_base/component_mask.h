#ifndef COMPONENT_MASK_HEADER
#define COMPONENT_MASK_HEADER
#include "component.h"

struct ComponentMask {
	unsigned int mask = 0;

	template<typename ComponentType>
	ComponentMask& add_component() {
		mask |= (1 << get_component_family<ComponentType>());
		return *this;
	}
	template<typename ComponentType>
	ComponentMask& remove_component() {
		mask &= ~(1 << get_component_family<ComponentType>());
		return *this;
	}
	bool is_new_match(ComponentMask oldMask, ComponentMask systemMask);
	bool is_no_longer_matched(ComponentMask oldMask, ComponentMask systemMask);
	bool matches(ComponentMask systemMask);
};
#endif
