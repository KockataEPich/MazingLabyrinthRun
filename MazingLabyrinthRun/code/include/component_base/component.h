#ifndef BASE_COMPONENT_HEADER
#define BASE_COMPONENT_HEADER
struct ComponentCounter {
	static int m_family_counter;
};

template<typename ComponentType>
struct Component {
	static inline int family() {
		static int family = ComponentCounter::m_family_counter++;
		return family;
	}
};

template<typename C>
static int get_component_family() {
	return Component<typename std::remove_const<C>::type>::family();
}
#endif
