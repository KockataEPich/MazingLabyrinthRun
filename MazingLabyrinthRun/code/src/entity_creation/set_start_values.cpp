#include "../include/entity_creation/set_start_values.h"

#include "../include/components/action_type_component.h"
#include "../include/components/animation_player_component.h"
#include "../include/components/facing_side_component.h"
#include "../include/components/player_component.h"
#include "../include/components/skin_component.h"
#include "../include/components/speed_component.h"
#include "../include/components/sprite_component.h"
#include "../include/components/transform_component.h"

namespace {
void initialize_player_values(EntityType entity_type, EntityHandle& entity) {
	entity.get_component<SpeedComponent>()->m_speed = 200.0f;
	entity.get_component<TransformComponent>()->m_scale = {6, 6};

	auto& skin = entity.get_component<SkinComponent>()->m_skin;
	skin = Skin::MAIN_CHARACTER_START_SKIN;

	auto& animation_player = entity.get_component<AnimationPlayerComponent>()->m_animation_player;
	animation_player.set_skin(skin);
	animation_player.play_animation(get_idle_animation(Skin::MAIN_CHARACTER_START_SKIN, FacingSide::down));

	auto& sprite = entity.get_component<SpriteComponent>()->m_sprite;
	sprite.setTexture(animation_player.get_current_texture());
	sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * sprite.getScale().x / 2.0f,
	                              sprite.getTexture()->getSize().y * sprite.getScale().y / 2.0f));
}

void initialize_components_regular_mobs(EntityType entity_type, EntityHandle& entity) {
	if (entity_type == EntityType::player) initialize_player_values(entity_type, entity);
}

void initialize_grass_land(EntityType entity_type, EntityHandle& entity){
	entity.get_component<TransformComponent>()->m_scale = {4, 4};
	auto& sprite = entity.get_component<SpriteComponent>()->m_sprite;
	sprite.setTexture(*ResourceManager::get_instance()->get_texture(Textures::ID::GRASS_LANDS_1));
}

void initialize_components_walkable_tile(EntityType entity_type, EntityHandle& entity) {
	if (entity_type == EntityType::grass_lands_1) initialize_grass_land(entity_type, entity);
}

}  // namespace

void initialize_entity_components(EntityType entity_type, EntityHandle& entity_handle) {
	if (is_regular_mob(entity_type)) initialize_components_regular_mobs(entity_type, entity_handle);
	if (is_walkalbe_tile(entity_type)) initialize_components_walkable_tile(entity_type, entity_handle);
}