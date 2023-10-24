#include <generated/systems/producer_systems/ai_system.h>
void AISystem::for_every_entity(
	Entity entity,
	TransformComponent& transform,
	SpeedComponent& speed,
	FacingSideComponent& facing_side){

	float delta_x = m_parent_world->get_player_sprite().getPosition().x - transform.position.x;
	float delta_y = m_parent_world->get_player_sprite().getPosition().y - transform.position.y;

	/*if (delta_x == 0 && delta_y == 0) continue;

	    if (delta_x != 0) {
	        if (delta_x > 0) side->m_side = FacingSide::right;
	        else side->m_side = FacingSide::left;
	        m_parent_world->add_event_component(entity, std::make_unique<MoveEventComponent>());
	    }
	    if (delta_y != 0) {
	        if (delta_y < 0) side->m_side = FacingSide::up;
	        else side->m_side = FacingSide::down;
	        m_parent_world->add_event_component(entity, std::make_unique<MoveEventComponent>());
	 }*/
}

