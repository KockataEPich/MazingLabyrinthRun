#ifndef BASE_SYSTEM_HEADER
#define BASE_SYSTEM_HEADER

#include "../entity/entity.h";


#include <set>

class System {
public:
	std::set<Entity> m_entities;
};

#endif