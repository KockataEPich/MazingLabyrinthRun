#include "../include/system/systems/collision_system.h"
#include "../include/component_base/component_handle.h"

sf::Vector2<float> change_transform_on_side(TransformComponent& transform, const SpeedComponent& speed, FacingSideComponent& side) { 
	switch (side.m_side) {
		case FacingSide::right:return {transform.m_position.x - speed.m_speed * 3, transform.m_position.y};
		case FacingSide::left: return {transform.m_position.x + speed.m_speed * 3, transform.m_position.y};
		case FacingSide::up: return {transform.m_position.x, transform.m_position.y + speed.m_speed * 3};
		case FacingSide::down: return {transform.m_position.x, transform.m_position.y - speed.m_speed * 3};
	}
}

void Collision::react(Entity const& entity) {
		ComponentHandle<TransformComponent> transform;
		ComponentHandle<SpeedComponent> speed;
		ComponentHandle<FacingSideComponent> side;
	    ComponentHandle<SolidComponent> solid;

		m_parent_world->unpack(entity, transform, side, speed, solid);
		for (auto solid_entity : m_solid_system->get_registered_entities()) { 
			if (entity == solid_entity) continue;
		    ComponentHandle<SolidComponent> solid_comp;
		    m_parent_world->unpack(solid_entity, solid_comp);
			if (solid->m_hitbox.intersects(solid_comp->m_hitbox)) { 
				transform->m_position = change_transform_on_side(*transform, *speed, *side);
			}
		}
} 