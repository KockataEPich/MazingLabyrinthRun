#ifndef SET_START_VALUES_HEADER
#define SET_START_VALUES_HEADER

#include "../entity_base/entity_handle.h"
#include "entity_list.h"

#include <any>
#include <unordered_map>

void initialize_entity_components(EntityType entity_type, EntityHandle& entity_handle);

#endif
