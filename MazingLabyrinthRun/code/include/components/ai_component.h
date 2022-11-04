#ifndef AI_COMPONENT_HEADER
#define AI_COMPONENT_HEADER

#include "../component_base/component.h"

// Stub for now. In the future will include behavior indication
struct AIComponent : public Component<AIComponent> {
	AIComponent() = default;
	bool is_ai = true;
};

#endif