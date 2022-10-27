#ifndef ENTITY_FACTORY_HEADER
#define ENTITY_FACTORY_HEADER

#include "../entity_base/entity_handle.h"
#include "entity_list.h"

#include <any>
#include <unordered_map>

void create_entity_type(EntityType entity_type, EntityHandle& entity_handle);

#endif
