#ifndef BASE_SYSTEM_HEADER
#define BASE_SYSTEM_HEADER

#include <bitset>
#include <vector>
#include "../component/componentMask.h"
#include "../entity/entity.h"

class World;

class System {
 public:
  System() = default;
  virtual ~System() = default;
  System(const System &) = default;
  System &operator=(const System &) = default;
  System(System &&) = default;
  System &operator=(System &&) = default;
  virtual void init(){};
  virtual void update(float dt){};
  virtual void render(){};
  void registerWorld(World *world);
  void registerEntity(Entity const &entity);
  void unRegisterEntity(Entity const &entity);
  ComponentMask getSignature();

 protected:
  std::vector<Entity> registeredEntities;
  World *parentWorld;
  ComponentMask signature;
};

#endif
