#ifndef RENDER_SYSTEM_HEADER
#define RENDER_SYSTEM_HEADER

#include "../../components/sprite_component.h"
#include "../../window/game_window.h"
#include "../../world/world.h"
#include "../system.h"

class Render : public System {
public:
	Render(GameWindow& render_window) : m_render_window{render_window} { m_signature.add_component<SpriteComponent>(); }
	void render() override;

private:
	GameWindow& m_render_window;
};

#endif