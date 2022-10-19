#ifndef BASE_COMPONENT_HEADER
#define BASE_COMPONENT_HEADER
#include "../include/entity/entity.h"
#include "componentManager.h"

#include <type_traits>

struct ComponentCounter {
	static int familyCounter;
};

template<typename ComponentType>
struct Component {
	static inline int family() {
		static int family = ComponentCounter::familyCounter++;
		return family;
	}
};

// Util method for getting family given type
template<typename C>
static int GetComponentFamily() {
	return Component<typename std::remove_const<C>::type>::family();
}
#endif
