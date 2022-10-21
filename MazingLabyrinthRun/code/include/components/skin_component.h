#ifndef SKIN_COMPONENT_HEADER
#define SKIN_COMPONENT_HEADER

#include "../"

class SkinComponent : public Component<SkinComponent> {
public:
	() = default;
	AnimationPlayer& animationPlayer() { return m_animation_player; };
private:
	m_animation_player;
};

#endif