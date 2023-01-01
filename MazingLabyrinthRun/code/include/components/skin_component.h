#ifndef SKIN_COMPONENT_HEADER
#define SKIN_COMPONENT_HEADER

#include "../resource/skins.h"
#include "../component_base/component.h"

struct SkinComponent : public Component<SkinComponent> {
	explicit SkinComponent(Skin&& skin) : m_skin{std::move(skin)} {};
	explicit SkinComponent() = default;
	Skin m_skin = Skin::DEFAULT_PLACEHOLDER_SKIN;
};

#endif