#include <component_base/component_handle.h>
#include <entity_base/entity_handle.h>
#include <system/systems/react_systems/attack_action_system.h>

#include <components/data_components/boundary_component.h>

#include <components/impulse_components/needle/basic_attack_needle.h>

#include <components/event_components/check_collision_event_component.h>

void AttackActionSystem::react(Entity const& entity) {
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<ActionTypeComponent> action;
	ComponentHandle<FacingSideComponent> side;
	
	m_parent_world->unpack(entity, transform, action, side);

	if (action->m_action_type != ActionType::attack) return;

	auto attack_box = m_parent_world->create_entity();
	attack_box.add_component(std::make_unique<BasicAttackNeedle>());
	attack_box.add_component(std::make_unique<BoundaryComponent>());
	
	auto atk_transform = std::make_unique<TransformComponent>();

	atk_transform->m_position.x = transform->m_position.x + 40;
	atk_transform->m_position.y = transform->m_position.y;
	atk_transform->m_scale = transform->m_scale;
	atk_transform->m_size.x = transform->m_size.x - 5;
	atk_transform->m_size.y = transform->m_size.y - 10;

	attack_box.add_component(std::move(atk_transform));
	m_parent_world->add_event_component(attack_box.entity, std::make_unique<CheckCollisionEventComponent>());
	attack_box.destroy();
}