#include <generated/systems/producer_systems/projectile_system.h>
#include <generated/components/basic_components/move_component.h>
void ProjectileSystem::for_every_entity(
        Entity entity,
        TargetForDirectionComponent& target_for_direction
    ){
	m_parent_world->add_event_component(entity, std::make_unique<MoveComponent>());
}