#ifndef PLAYER_HEADER_H
#define PLAYER_HEADER_H

#include "../include/entityBase/complexWorldObject/activeObject.h"
#include "../include/entityBase/complexWorldObject/compoundWorldObject.h"
#include "playerTextureEnum.h"
#include "playerLogic.h"
#include "playerView.h"

#include <SFML/Graphics/Texture.hpp>

class Player
    : public ActiveObject<PlayerState>
    , public CompoundWorldObject<PlayerComponents> {
public:
	Player() : ActiveObject(std::move(std::make_unique<PlayerLogic>(componentsMap())), std::move(std::make_unique<PlayerView>(componentsMap()))){};

private:
	void initializeComponentSpriteMap(
	    std::unordered_map<PlayerComponents, std::optional<std::unique_ptr<ComponentSprite>>>&) override;

};

#endif