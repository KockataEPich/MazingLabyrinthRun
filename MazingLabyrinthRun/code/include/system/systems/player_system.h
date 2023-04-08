#ifndef PLAYER_SYSTEM_HEADER
#define PLAYER_SYSTEM_HEADER

#include "../../components/action_type_component.h"
#include "../../components/facing_side_component.h"
#include "../../components/player_component.h"
#include "../../components/speed_component.h"
#include "../../components/transform_component.h"
#include "../../window/game_window.h"
#include "../../world/world.h"
#include "../system.h"

#include <components/status_list_component.h>

class Player : public ProducerSystem {
public:
	Player() {
		m_signature.add_component<PlayerComponent>()
		    .add_component<TransformComponent>()
		    .add_component<SpeedComponent>()
		    .add_component<ActionTypeComponent>()
		    .add_component<FacingSideComponent>()
		    .add_component<StatusListComponent>();
	}
	void init() override { m_registered_entities.reserve(1); }  // Only one player
	void update() override;
};

#endif