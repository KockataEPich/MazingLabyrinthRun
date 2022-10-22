#ifndef SKIN_COMPONENT_HEADER
#define SKIN_COMPONENT_HEADER

#include "../resource/skins.h"

struct SkinComponent : public Component<SkinComponent> {
	explicit SkinComponent(Skin&& skin) : m_skin{std::move(skin)} {};
	Skin& m_skin;
};

#endif