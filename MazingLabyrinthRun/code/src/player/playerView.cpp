#include "../include/player/playerView.h"

PlayerView::PlayerView()
    : AnimatedView<PlayerState>(Skin::MAIN_CHARACTER_START_SKIN,
                                {Animation(Textures::ID::NORRIS_NAKED_DEF_RIGHT_1),
                                 Animation(Textures::ID::NORRIS_NAKED_DEF_LEFT_1),
                                 Animation(Textures::ID::NORRIS_NAKED_DEF_UP_1),
                                 Animation(Textures::ID::NORRIS_NAKED_DEF_DOWN_1)}) {}
