#ifndef MOVE_SYSTEM_HEADER
#define MOVE_SYSTEM_HEADER

#include "system.h"
#include "../include/world/coordinator.h"
#include "../include/components/move_components.h"

extern Coordinator gCoordinator;

class MoveSystem : public System{
public:
	void init() {};
	void update(float delta_time) {
	    for(auto const& entity : m_entities){
	    	auto& transform = gCoordinator.get_component<Transform>(entity);
	    	transform.x += transform.x += 1.0f * (delta_time / 1000.0f);
		}

	};
};

#endif