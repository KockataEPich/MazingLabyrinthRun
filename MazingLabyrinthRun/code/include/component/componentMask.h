#ifndef COMPONENT_MASK_HEADER
#define COMPONENT_MASK_HEADER
#include "component.h"

struct ComponentMask {
	unsigned int mask = 0;
	template<typename ComponentType>
	void add_component() {
		mask |= (1 << get_component_family<ComponentType>());
	}
	template<typename ComponentType>
	void remove_component() {
		mask &= ~(1 << get_component_family<ComponentType>());
	}
	bool is_new_match(ComponentMask oldMask, ComponentMask systemMask);
	bool is_no_longer_matched(ComponentMask oldMask, ComponentMask systemMask);
	bool matches(ComponentMask systemMask);
};
#endif
