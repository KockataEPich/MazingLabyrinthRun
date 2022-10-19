#ifndef ENTITY_MANAGER_HEADER
#define ENTITY_MANAGER_HEADER
#include "entity.h"

class EntityManager {
 public:
  Entity createEntity();
  void destroy(Entity entity);

 private:
  int lastEntity = 0;
};
#endif
