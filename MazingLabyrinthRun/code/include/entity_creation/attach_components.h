#ifndef ATTACH_COMPONENTS_TO_TYPE_HEADER
#define ATTACH_COMPONENTS_TO_TYPE_HEADER

#include "../entity_base/entity_handle.h"
#include "entity_list.h"

#include <any>
#include <unordered_map>

void attach_components_to_type(EntityType entity_type, EntityHandle& entity);

#endif
