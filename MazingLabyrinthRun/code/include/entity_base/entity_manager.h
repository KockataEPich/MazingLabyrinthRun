#ifndef ENTITY_MANAGER_HEADER
#define ENTITY_MANAGER_HEADER
#include "entity.h"

class EntityManager {
public:
	Entity create_entity();
	void destroy(Entity entity);

private:
	int last_entity = 0;
};
#endif
