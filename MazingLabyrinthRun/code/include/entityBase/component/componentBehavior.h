#ifndef I_COMPONENT_BEHAVIOR_HEADER_H
#define I_COMPONENT_BEHAVIOR_HEADER_H

#include <SFML/Graphics/Sprite.hpp>
class IComponentBehavior {
public:
	virtual void modifySprite(sf::Sprite* sprite, int frameNumber) = 0;
};

#endif