#include <generated/systems/event_systems/update_boundary_from_transform_system.h>
#include <utils/sfml_vector_helpers.h>
void UpdateBoundaryFromTransformSystem::p_handle_event(
        EntityHandle entity,
        BoundaryComponent& boundary,
		TransformComponent& transform,
		SkinComponent& skin,
        UpdateBoundaryFromTransformEvent& update_boundary_from_transform
    ){
	auto& offsets = get_boundary_side_offsets_of_skin.at(skin.skin);
	auto scaled_size = transform.get_scaled_size();
	boundary.hitbox = {
	    (transform.position.x - scaled_size.x * 0.5f) + scaled_size.x * (1 - offsets.left),
	    (transform.position.y - scaled_size.y * 0.5f) + scaled_size.y * (1 - offsets.top),
	    scaled_size.x * offsets.width - scaled_size.x * (1 - offsets.left),
	    scaled_size.y * offsets.height - scaled_size.y * (1 - offsets.top)
	};
}