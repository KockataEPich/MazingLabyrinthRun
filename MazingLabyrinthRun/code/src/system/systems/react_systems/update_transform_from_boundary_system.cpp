#include <generated/systems/react_systems/update_transform_from_boundary_system.h>
void UpdateTransformFromBoundarySystem::react_on_entity(
        EntityHandle entity,
        TransformComponent& transform,
		BoundaryComponent& boundary,
		SkinComponent& skin
    ){
	auto& offsets = get_boundary_side_offsets_of_skin.at(skin.skin);
	auto scaled_size = transform.get_scaled_size();
	transform.position = {
	    (boundary.hitbox.left - scaled_size.x * (1 - offsets.left)) + scaled_size.x * 0.5f,
	    (boundary.hitbox.top - scaled_size.y * (1 - offsets.top)) + scaled_size.y * 0.5f,
	};
}