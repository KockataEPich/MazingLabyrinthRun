#include "../include/entity_creation/attach_components.h"

#include "../include/components/action_type_component.h"
#include "../include/components/animation_player_component.h"
#include "../include/components/facing_side_component.h"
#include "../include/components/player_component.h"
#include "../include/components/skin_component.h"
#include "../include/components/speed_component.h"
#include "../include/components/sprite_component.h"
#include "../include/components/transform_component.h"

namespace {
void attach_player_components(EntityType entity_type, EntityHandle& entity) {
	entity.add_component(std::make_unique<PlayerComponent>());
}

void attach_regular_mob_components(EntityType entity_type, EntityHandle& entity) {
	entity.add_component(std::make_unique<TransformComponent>())
	    .add_component(std::make_unique<ActionTypeComponent>())
	    .add_component(std::make_unique<SpeedComponent>())
	    .add_component(std::make_unique<FacingSideComponent>())
	    .add_component(std::make_unique<SkinComponent>())
	    .add_component(std::make_unique<AnimationPlayerComponent>());

	if (entity_type == EntityType::player) attach_player_components(entity_type, entity);
}

void attach_walkable_tile_components(EntityType entity_type, EntityHandle& entity) {}
}  // namespace

void attach_components_to_type(EntityType entity_type, EntityHandle& entity) {
	entity.add_component(std::make_unique<SpriteComponent>()).add_component(std::make_unique<TransformComponent>());

	if (is_regular_mob(entity_type)) attach_regular_mob_components(entity_type, entity);
	if (is_walkalbe_tile(entity_type)) attach_walkable_tile_components(entity_type, entity);
}