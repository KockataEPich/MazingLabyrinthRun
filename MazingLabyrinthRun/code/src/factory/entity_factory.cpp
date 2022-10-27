#include "../include/factory/entity_factory.h"

#include "../include/components/action_type_component.h"
#include "../include/components/animation_player_component.h"
#include "../include/components/facing_side_component.h"
#include "../include/components/player_component.h"
#include "../include/components/speed_component.h"
#include "../include/components/skin_component.h"
#include "../include/components/sprite_component.h"
#include "../include/components/transform_component.h"

namespace {
void create_player(EntityType entity_type, EntityHandle& entity) {
	DefaultAnimations default_animation{Animation(Textures::ID::NORRIS_NAKED_DEF_RIGHT_1),
	                                    Animation(Textures::ID::NORRIS_NAKED_DEF_LEFT_1),
	                                    Animation(Textures::ID::NORRIS_NAKED_DEF_UP_1),
	                                    Animation(Textures::ID::NORRIS_NAKED_DEF_DOWN_1)};
	entity.add_component(std::make_unique<AnimationPlayerComponent>(std::move(default_animation)))
	    .add_component(std::make_unique<PlayerComponent>())
	    .add_component(std::make_unique<SkinComponent>(Skin::MAIN_CHARACTER_START_SKIN));

	auto& speed = entity.get_component<SpeedComponent>()->m_speed;
	speed = 200.0f;

	auto& position = entity.get_component<TransformComponent>()->m_position;
	position.x = 0.0f;
	position.y = 0.0f;

	auto& scale = entity.get_component<TransformComponent>()->m_scale;
	scale.x = 6;
	scale.y = 6;

	auto& sprite = entity.get_component<SpriteComponent>()->m_sprite;
	sprite.setTexture(entity.get_component<AnimationPlayerComponent>()->m_animation_player.get_current_texture());
	sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * sprite.getScale().x / 2.0f,
	                              sprite.getTexture()->getSize().y * sprite.getScale().y / 2.0f));
}

void create_regular_mob(EntityType entity_type, EntityHandle& entity) {
	entity.add_component(std::make_unique<SpriteComponent>())
	    .add_component(std::make_unique<ActionTypeComponent>())
	    .add_component(std::make_unique<TransformComponent>())
	    .add_component(std::make_unique<SpeedComponent>())
	    .add_component(std::make_unique<FacingSideComponent>());

	if (entity_type == EntityType::player) create_player(entity_type, entity);
}

bool is_regular_mob(EntityType type) { return static_cast<int>(type) >= 0 && static_cast<int>(type) < 100; }

}  // namespace

void create_entity_type(EntityType entity_type, EntityHandle& entity_handle) {
	if (is_regular_mob(entity_type)) create_regular_mob(entity_type, entity_handle);
}
