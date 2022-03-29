#ifndef I_INTERACTABLE_OBJECT_HEADER_H
#define I_INTERACTABLE_OBJECT_HEADER_H

#include "iWorldObject.h"

class IInteracatableObject : public IWorldObject {
public:
	virtual void interact() = 0;
};

#endif