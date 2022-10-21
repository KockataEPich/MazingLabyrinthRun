#ifndef ACTION_TYPE_COMPONENT_HEADER
#define ACTION_TYPE_COMPONENT_HEADER

#include "../resource/skins.h"

struct SkinComponent : public Component<SkinComponent> {
	SkinComponent(Skin&& skin){m_skin{skin}};
	Skin& m_skin;
};

#endif