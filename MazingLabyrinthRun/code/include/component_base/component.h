#ifndef BASE_COMPONENT_HEADER
#define BASE_COMPONENT_HEADER
#include "../entity_base/entity.h"
#include "component_manager.h"

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
static int get_component_family() {
	return Component<typename std::remove_const<C>::type>::family();
}
#endif
