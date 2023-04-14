#ifndef ANIMATED_ENTITY_COMPONENT_INITIALIZER
#define ANIMATED_ENTITY_COMPONENT_INITIALIZER

#include "../../../resource/skins.h"
#include "../component_initializer.h"

class AnimatedDrawableInitializer : public ComponentInitializer {
public:
	AnimatedDrawableInitializer(Skin skin, float speed) : m_skin{skin}, m_speed{speed} {}

	void initialize_components(EntityHandle& entity) override {
		entity.get_component<SpeedComponent>()->m_speed = m_speed;
		entity.get_component<TransformComponent>()->m_scale = m_default_scale;

		auto& skin = entity.get_component<SkinComponent>()->m_skin;
		skin = m_skin;

		auto& animation_player = entity.get_component<AnimationPlayerComponent>()->m_animation_player;
		animation_player.set_skin(skin);
		animation_player.play_animation(get_idle_animation(skin, FacingSide::down));

		auto& sprite = entity.get_component<SpriteComponent>()->m_sprite;
		sprite.setScale(entity.get_component<TransformComponent>()->m_scale);
		sprite.setTexture(animation_player.get_current_texture());
		//sprite.setOrigin(sf::Vector2f(animation_player.get_current_rect().width / 2.0f, 
		//							  animation_player.get_current_rect().height / 2.0f));
	};
private:
	Skin m_skin;
	float m_speed;
};

#endif