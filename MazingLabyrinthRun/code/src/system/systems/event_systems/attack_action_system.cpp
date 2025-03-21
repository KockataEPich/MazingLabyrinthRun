#include <generated/systems/event_systems/attack_action_system.h>
#include <generated/components/basic_components/basic_attack_needle_component.h>
#include <generated/components/data_components/boundary_component.h>
#include <entity_base/entity_handle.h>

void AttackActionSystem::p_handle_event(
	EntityHandle entity,
	ActionTypeComponent& action_type,
	FacingSideComponent& facing_side,
	TransformComponent& transform,
	InitiateAttackEvent& initiate_attack) { 
	
	//if (action_type.action_type != ActionType::attack) return;
	//
	//auto attack_box = m_game->create_entity();
	//attack_box.add_components(std::make_unique<BasicAttackNeedleComponent>());
	//attack_box.add_components(std::make_unique<BoundaryComponent>());

	//auto atk_transform = std::make_unique<TransformComponent>();

	//atk_transform->position.x = transform.position.x + 40;
	//atk_transform->position.y = transform.position.y;
	//atk_transform->scale = transform.scale;
	//atk_transform->size.x = transform.size.x - 5;
	//atk_transform->size.y = transform.size.y - 10;

	//attack_box.add_components(std::move(atk_transform));
	//attack_box.add_event_components<CollisionCheckComponent>();
	//attack_box.destroy();

}

