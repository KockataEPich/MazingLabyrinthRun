#ifndef COMPONENT_SPRITE_HEADER_H
#define COMPONENT_SPRITE_HEADER_H

#include "../include/attribute/facingSide.h"
#include "../include/entityBase/component/componentBehavior.h"
#include "../include/entityBase/worldObject.h"

class ComponentSprite : public WorldObject {
public:
	virtual void setDefaultImage(const FacingSide& side) = 0;
	void modifySprite(int frameNumber) { m_componentBehavior->modifySprite(m_sprite.get(), frameNumber); };

	virtual void setComponentBehavior(std::unique_ptr<IComponentBehavior>& componentBehavior) {
		m_componentBehavior = std::move(componentBehavior);
	}

private:
	std::unique_ptr<IComponentBehavior> m_componentBehavior;
};

#endif