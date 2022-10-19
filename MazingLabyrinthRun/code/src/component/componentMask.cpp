#include "../include/component/componentMask.h"

bool ComponentMask::is_new_match(ComponentMask oldMask, ComponentMask systemMask) {
	return matches(systemMask) && !oldMask.matches(systemMask);
}

bool ComponentMask::is_no_longer_matched(ComponentMask oldMask, ComponentMask systemMask) {
	return oldMask.matches(systemMask) && !matches(systemMask);
}

bool ComponentMask::matches(ComponentMask systemMask) { return ((mask & systemMask.mask) == systemMask.mask); }
