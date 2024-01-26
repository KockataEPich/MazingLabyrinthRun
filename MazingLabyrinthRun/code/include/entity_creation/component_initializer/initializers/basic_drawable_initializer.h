#ifndef BASIC_DRAWABLE_ENTITY_COMPONENT_INITIALIZER
#define BASIC_DRAWABLE_ENTITY_COMPONENT_INITIALIZER

#include "../../../resource/texture_enum.h"
#include "../component_initializer.h"
#include <resource/resource_manager.h>

class BasicDrawableInitializer : public ComponentInitializer {
public:
	BasicDrawableInitializer(Textures::ID texture) : m_texture{texture} {}

	void initialize_components(EntityHandle& entity) override {
		entity.get_component<TransformComponent>()->scale = m_default_scale;
		auto& sprite = entity.get_component<SpriteComponent>()->sprite;
		sprite.setTexture(*ResourceManager::get_instance()->get_texture(m_texture));
		entity.get_component<TransformComponent>()->size = {(float)sprite.getTextureRect().width,
		                                                      (float)sprite.getTextureRect().height};
	};

private:
	Textures::ID m_texture;
};

#endif