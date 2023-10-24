#include <generated/systems/react_systems/attack_action_system.h>
#include <generated/components/basic_components/basic_attack_needle_component.h>
#include <generated/components/data_components/boundary_component.h>
#include <generated/components/basic_components/collision_check_component.h>

void AttackActionSystem::react_on_entity(
	Entity entity,
	ActionTypeComponent& action_type,
	FacingSideComponent& facing_side,
	TransformComponent& transform){ 
	
	if (action_type.action_type != ActionType::attack) return;

	auto attack_box = m_parent_world->create_entity();
	attack_box.add_component(std::make_unique<BasicAttackNeedleComponent>());
	attack_box.add_component(std::make_unique<BoundaryComponent>());

	auto atk_transform = std::make_unique<TransformComponent>();

	atk_transform->position.x = transform.position.x + 40;
	atk_transform->position.y = transform.position.y;
	atk_transform->scale = transform.scale;
	atk_transform->size.x = transform.size.x - 5;
	atk_transform->size.y = transform.size.y - 10;

	attack_box.add_component(std::move(atk_transform));
	m_parent_world->add_event_component(attack_box.entity, std::make_unique<CollisionCheckComponent>());
	attack_box.destroy();

}

