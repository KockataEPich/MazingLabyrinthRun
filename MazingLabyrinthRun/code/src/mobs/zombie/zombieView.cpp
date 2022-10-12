#include "../include/mobs/zombie/zombieView.h"

ZombieView::ZombieView()
    : AnimatedView<ZombieState>(Skin::ZOMBIE_DEFAULT_SKIN,
                                {Animation(Textures::ID::ZOMBIE_IDLE_LEFT),
								 Animation(Textures::ID::ZOMBIE_IDLE_LEFT),
                                 Animation(Textures::ID::ZOMBIE_IDLE_LEFT),
                                 Animation(Textures::ID::ZOMBIE_IDLE_LEFT)}) {}
