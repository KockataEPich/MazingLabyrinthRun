#ifndef ANIMATED_ENTITY_COMPONENT_INITIALIZER
#define ANIMATED_ENTITY_COMPONENT_INITIALIZER

#include "../../../resource/skins.h"
#include "../component_initializer.h"

class AnimatedDrawableInitializer : public ComponentInitializer {
public:
	AnimatedDrawableInitializer(Skin skin, float speed) : m_skin{skin}, m_speed{speed} {}

	void initialize_components(EntityHandle& entity) override {
		entity.get_component<SpeedComponent>()->speed = m_speed;
		entity.get_component<TransformComponent>()->scale = m_default_scale;

		
		auto& skin = entity.get_component<SkinComponent>()->skin;
		skin = m_skin;

		auto& animation_player = entity.get_component<AnimationPlayerComponent>()->animation_player;
		animation_player.set_skin(skin);
		animation_player.play_animation(get_idle_animation(skin));

		auto& sprite = entity.get_component<SpriteComponent>()->sprite;
		sprite.setScale(entity.get_component<TransformComponent>()->scale);
		sprite.setTexture(animation_player.get_current_texture());
		sprite.setOrigin(sf::Vector2f(animation_player.get_current_rect().width / 2.0f, 
									  animation_player.get_current_rect().height / 2.0f));
		entity.get_component<TransformComponent>()->size = {(float)sprite.getTextureRect().width,
		                                                      (float)sprite.getTextureRect().height};
	};
private:
	Skin m_skin;
	float m_speed;
};

#endif