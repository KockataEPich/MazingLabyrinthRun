#include <game.h>
#include <entity_base/entity_handle.h>

#include <generated/events/update_mouse_position_event.h>
EntityHandle Game::create_entity() { return {entities->birth_entity(), this}; }

void Game::update_ui() { 
	ui_manager->update_ui();
	event_bus->publish(mouse, UpdateMousePositionEvent());
}