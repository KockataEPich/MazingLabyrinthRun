#ifndef PLAYER_SYSTEM_HEADER
#define PLAYER_SYSTEM_HEADER

#include <components/data_components/action_type_component.h>
#include <components/data_components/facing_side_component.h>
#include <components/data_components/target_for_direction_component.h>
#include <components/data_components/player_component.h>
#include <components/data_components/speed_component.h>
#include <components/data_components/transform_component.h>
#include <window/game_window.h>
#include <world/world.h>
#include <system/system.h>

class Player : public ProducerSystem {
public:
	Player() {
		m_signature.add_component<PlayerComponent>()
		    .add_component<TransformComponent>()
		    .add_component<SpeedComponent>()
		    .add_component<TargetForDirection>()
		    .add_component<ActionTypeComponent>()
		    .add_component<FacingSideComponent>();
	}
	void init() override { m_registered_entities.reserve(1); }  // Only one player
	void update() override;
};

#endif