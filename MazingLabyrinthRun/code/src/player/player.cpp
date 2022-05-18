#include "../include/player/player.h"

void Player::initializeComponentSpriteMap(
    std::unordered_map<PlayerComponents, std::optional<std::unique_ptr<ComponentSprite>>>& components) {
	components[PlayerComponents::sword] = std::make_unique<ComponentSprite>();
}