#include <game.h>
#include <entity_base/entity_handle.h>

EntityHandle Game::create_entity() { return {entities->birth_entity(), this}; }

void Game::update_ui() { 
	ui_manager->update_ui();
	add_event_components<UpdateMousePositionComponent>(mouse);
}