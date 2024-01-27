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

#include <generated/systems/render_systems/render_sprite_system.h>
#include <generated/systems/render_systems/render_health_system.h>

#include <generated/systems/impulse_systems/basic_collision_system.h>
#include <generated/systems/impulse_systems/basic_damage_system.h>
#include <generated/systems/impulse_systems/projectile_collision_system.h>

#include <game.h>

namespace {
void update_mask_in_systems(const Entity entity,
                            ComponentMask new_mask,
                            ComponentMask old_mask,
                            EntityTrackerSystem* system) {
	ComponentMask systemSignature = system->get_signature();
	if (new_mask.is_new_match(old_mask, systemSignature))
		system->register_entity(entity);
	else if (new_mask.is_no_longer_matched(old_mask, systemSignature))
		system->unregister_entity(entity);
}
}  // namespace

void Systems::update_entity_system_subscriptions(const Entity entity, ComponentMask old_mask) {
	for (auto& system : m_producer_system_sequence_wrapper.get_systems())
		update_mask_in_systems(entity, m_game->entities->get_mask(entity), old_mask, system.get());
	for (auto& system : m_render_systems)
		update_mask_in_systems(entity, m_game->entities->get_mask(entity), old_mask, system.get());
}

void Systems::react_on_event(const Entity entity, ComponentMask new_mask) {
	for (auto& system : m_react_systems)
		if (new_mask.matches(system->get_signature())) system->react(entity);
}

void Systems::exchange_impulses(const Entity initiator, const Entity& victim) {
	for (auto& system : m_impulse_systems) {
		if (m_game->entities->get_mask(initiator).matches(system->get_signature()) &&
		    m_game->entities->get_mask(victim).matches(system->get_signature_of_victim()))
			system->exchange_impulse(initiator, victim);
	}
}

void Systems::remove_entity_from_systems(const Entity entity) {
	for (auto& system : m_producer_system_sequence_wrapper.get_systems())
		if (m_game->entities->get_mask(entity).matches(system->get_signature())) system->unregister_entity(entity);

	for (auto& system : m_render_systems)
		if (m_game->entities->get_mask(entity).matches(system->get_signature())) system->unregister_entity(entity);
}

void Systems::init(){
	add_react_systems(
		std::make_unique<MoveSystem>(),
		std::make_unique<CollisionDetectionSystem>(),
	    std::make_unique<AttackActionSystem>());

	add_impulse_systems(
		std::make_unique<BasicCollisionSystem>(),
		std::make_unique<BasicDamageSystem>(),
		std::make_unique<ProjectileCollisionSystem>());

	add_producer_systems(
		std::make_unique<PlayerSystem>(*m_game->m_window),
		std::make_unique<AISystem>(),
		std::make_unique<AnimateSystem>(),
		std::make_unique<TransformSystem>(),
		std::make_unique<ProjectileSystem>(),
	    std::make_unique<UpdateCrosshairPositionSystem>(*m_game->m_window));

	add_render_systems(std::make_unique<RenderSpriteSystem>(*m_game->m_window),
	                   std::make_unique<RenderHealthSystem>(*m_game->m_window));

	for (auto& system : m_producer_system_sequence_wrapper.get_systems()) system->init();
	for (auto& system : m_react_systems) system->init();
	for (auto& system : m_impulse_systems) system->init();
	for (auto& system : m_render_systems) system->init();
};