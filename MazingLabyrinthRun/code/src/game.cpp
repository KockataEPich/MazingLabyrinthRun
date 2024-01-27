#include <game.h>
#include <entity_base/entity_handle.h>

EntityHandle Game::create_entity() { return {entities->birth_entity(), this}; }