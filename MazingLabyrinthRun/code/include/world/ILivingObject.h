#ifndef I_LIVING_OBJECT_HEADER_H
#define I_LIVING_OBJECT_HEADER_H

#include "iWorldObject.h"

class ILivingObject : public IWorldObject {
public:
	virtual void doBehavior(const float delta) = 0;

protected:
	float m_movementSpeed;
};

#endif