#ifndef PLAYER_COMPONENT_HEADER
#define PLAYER_COMPONENT_HEADER

#include <component_base/component.h>
struct PlayerComponent : public Component<PlayerComponent> {
private:
	bool is_player = true;  // This will be changed in the future to a pointer to the UI information
};

#endif