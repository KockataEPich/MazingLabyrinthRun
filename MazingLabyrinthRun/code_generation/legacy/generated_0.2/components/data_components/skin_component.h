// ################## THIS FILE IS GENERATED ##################
#ifndef SKIN_COMPONENT_HEADER
#define SKIN_COMPONENT_HEADER

#include <component_base/component.h>
#include <resource/skins.h>

struct SkinComponent : public Component<SkinComponent> {
	SkinComponent() = default;
	explicit SkinComponent(
		Skin&& skin) : 
		skin{std::move(skin)}{}

	Skin skin = Skin::DEFAULT_PLACEHOLDER_SKIN;
};
#endif