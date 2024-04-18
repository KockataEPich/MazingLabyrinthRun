#include <generated/systems/producer_systems/check_crosshair_collision_system.h>
void CheckCrosshairCollisionSystem::for_every_entity(EntityHandle entity,
													 BoundaryComponent& boundary){
	auto potential_overlaps = m_game->quad_tree->get_potential_collisions(boundary.hitbox, {0, 0});
	for (auto overlapping_entity : potential_overlaps) {
		auto overlapping_boundary =
		    std::get<0>(m_game->components->unpack<BoundaryComponent>(overlapping_entity))->hitbox;

		if (boundary.hitbox.intersects(overlapping_boundary))
			m_game->systems->exchange_impulses(entity.entity, overlapping_entity, {});
	}
}