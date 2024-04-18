#include <system/systems.h>

#include <generated/systems/producer_systems/ai_system.h>
#include <generated/systems/producer_systems/animate_system.h>
#include <generated/systems/producer_systems/player_system.h>
#include <generated/systems/producer_systems/transform_system.h>
#include <generated/systems/producer_systems/update_crosshair_position_system.h>
#include <generated/systems/producer_systems/projectile_system.h>

#include <generated/systems/react_systems/collision_detection_system.h>
#include <generated/systems/react_systems/move_system.h>
#include <generated/systems/react_systems/attack_action_system.h>
#include <generated/systems/react_systems/update_boundary_from_transform_system.h>
#include <generated/systems/react_systems/update_transform_from_boundary_system.h>

#include <generated/systems/render_systems/render_sprite_system.h>
#include <generated/systems/render_systems/render_health_system.h>
#include <generated/systems/render_systems/render_quad_tree_system.h>

#include <generated/systems/impulse_systems/basic_collision_system.h>
#include <generated/systems/impulse_systems/basic_damage_system.h>
#include <generated/systems/impulse_systems/projectile_collision_system.h>

#include <game.h>
#include <system/system_utils.h>

void Systems::update_entity_system_subscriptions(const Entity entity, ComponentMask old_mask) {
	auto new_mask = m_game->entities->get_mask(entity);

	m_producer_system_sequence_wrapper.update_systems_registrations(entity, new_mask,old_mask);
	for (auto& system : m_render_systems) update_system_registration(entity, new_mask, old_mask, system.get());
}

void Systems::react_on_event(const Entity entity, ComponentMask new_mask) {
	for (auto& system : m_react_systems) 
		if (new_mask.matches(system->get_signature())) system->react(entity);
}

void Systems::exchange_impulses(const Entity initiator, 
								const Entity& victim, 
								const CollisionInfo& collision_info) {
	for (auto& system : m_impulse_systems) {
		if (m_game->entities->get_mask(initiator).matches(system->get_signature()) &&
		    m_game->entities->get_mask(victim).matches(system->get_signature_of_victim()))
			system->exchange_impulse(initiator, victim, collision_info);
	}
}

void Systems::remove_entity_from_systems(const Entity entity) {
	auto mask = m_game->entities->get_mask(entity);

	m_producer_system_sequence_wrapper.remove_entity_from_systems(entity, mask);

	for (auto& system : m_render_systems)
		if (mask.matches(system->get_signature())) system->unregister_entity(entity);
}

void Systems::init(){
	add_react_systems(
		std::make_unique<MoveSystem>(),
	    std::make_unique<CollisionDetectionSystem>(),
	    std::make_unique<AttackActionSystem>(),
		std::make_unique<UpdateBoundaryFromTransformSystem>(),
	    std::make_unique<UpdateTransformFromBoundarySystem>());

	add_impulse_systems(
		std::make_unique<BasicCollisionSystem>(),
		std::make_unique<BasicDamageSystem>(),
		std::make_unique<ProjectileCollisionSystem>());

	add_producer_systems(
		std::make_unique<PlayerSystem>(*m_game->m_window),
		std::make_unique<AISystem>(),
		std::make_unique<AnimateSystem>(),
		std::make_unique<ProjectileSystem>(),
	    std::make_unique<TransformSystem>());

	add_non_tick_dependent_producer_system(
		std::make_unique<UpdateCrosshairPositionSystem>(*m_game->m_window));

	add_render_systems(std::make_unique<RenderSpriteSystem>(*m_game->m_window),
	                   std::make_unique<RenderQuadTreeSystem>(*m_game->m_window),
	                   std::make_unique<RenderHealthSystem>(*m_game->m_window));

	m_producer_system_sequence_wrapper.init();
	for (auto& system : m_react_systems) system->init();
	for (auto& system : m_impulse_systems) system->init();
	for (auto& system : m_render_systems) system->init();
};