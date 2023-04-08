#ifndef ANIMATE_SYSTEM_HEADER
#define ANIMATE_SYSTEM_HEADER

#include "../../components/sprite_component.h"
#include "../../components/action_type_component.h"
#include "../../components/animation_player_component.h"
#include "../../components/facing_side_component.h"
#include "../../components/skin_component.h"
#include "../system.h"
#include "../../world/world.h"

class Animate : public ProducerSystem {
public:
	Animate(){
		m_signature.add_component<ActionTypeComponent>()
			.add_component<FacingSideComponent>()
			.add_component<SkinComponent>()
			.add_component<AnimationPlayerComponent>()
			.add_component<SpriteComponent>();
	}
	void update() override;
};

#endif