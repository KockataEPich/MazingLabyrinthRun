#ifndef PLAYER_TEXTURE_ENUM_H
#	define PLAYER_TEXTURE_ENUM_H

#	include "../resource/textureEnum.h"

static std::vector<Textures::ID> runRightAnimation{Textures::ID::NORRIS_NAKED_WALK_RIGHT_1,
                                                   Textures::ID::NORRIS_NAKED_WALK_RIGHT_2,
                                                   Textures::ID::NORRIS_NAKED_WALK_RIGHT_1,
                                                   Textures::ID::NORRIS_NAKED_WALK_RIGHT_3};
static std::vector<Textures::ID> runLeftAnimation{Textures::ID::NORRIS_NAKED_WALK_LEFT_1,
                                                  Textures::ID::NORRIS_NAKED_WALK_LEFT_2,
                                                  Textures::ID::NORRIS_NAKED_WALK_LEFT_1,
                                                  Textures::ID::NORRIS_NAKED_WALK_LEFT_3};
static std::vector<Textures::ID> runUpAnimation{Textures::ID::NORRIS_NAKED_WALK_UP_1,
                                                Textures::ID::NORRIS_NAKED_WALK_UP_2,
                                                Textures::ID::NORRIS_NAKED_WALK_UP_1,
                                                Textures::ID::NORRIS_NAKED_WALK_UP_3};
static std::vector<Textures::ID> runDownAnimation{Textures::ID::NORRIS_NAKED_WALK_DOWN_1,
                                                  Textures::ID::NORRIS_NAKED_WALK_DOWN_2,
                                                  Textures::ID::NORRIS_NAKED_WALK_DOWN_1,
                                                  Textures::ID::NORRIS_NAKED_WALK_DOWN_3};

static std::vector<Textures::ID> defaultDownAnimation{Textures::ID::NORRIS_NAKED_WALK_DOWN_1};
static std::vector<Textures::ID> defaultUpAnimation{Textures::ID::NORRIS_NAKED_WALK_UP_1};
static std::vector<Textures::ID> defaultLeftAnimation{Textures::ID::NORRIS_NAKED_WALK_LEFT_1};
static std::vector<Textures::ID> defaultRightAnimation{Textures::ID::NORRIS_NAKED_WALK_RIGHT_1};

enum class PlayerComponents { hat };

#endif

// std::tuple<sf::Vector2f, PlayerComponentsSprites>
//  WorldObject{
// std::map<T, sprite>
//}

// template <typename T, typename U>
// class ComponentsToAnimate {
// public:
// ComponentsToAnimate(std::map<T, sprite>)
// std::map<T, > getObjectComponents();
// enum class PlayerBareStationaryAnimations {1, 2, 3, 4};
//};

// AnimationPlayer(Looks)
//  m_looks = looks;
//
//
// playAnimation(Animation){
//  for( frame : animation.getAllFrames())
//		looks.
// }

// UpdateTexturesOnLooks

/*
left,right, up, down

Animation(){
    Looks;
    Looks(FacePosition, std::map<T, IWorldObject>){
        for(object : objectsInPLayer)


    }
    {

    }
}

State{
FacingSide
Animation
}


animationName = running;
FacingSide = right;


fronetendWorldObject(state){
    AnimationEnum exactAnimation = getProperAnimation(state) //runRightAnimation


}

getProperAnimation(){
switch(state.animationName)
    case:running
        properRunningAnimation(state.Side)
}

properRunningAnimation(side){
    switch(side)
        case: right

}
static std::vector<std::vector<PlayerTextures>> swordSlash{PlayerTextures::right, PlayerTeextures::right2};

// WorldObject{
public:
    update(){
        IState* state = backendWorldObject.updateBehavior();
        fronetendWorldObject.update(state);
    }

private:
    backendWorldObject;
    frontendWorldObject(textures);

    unique_ptr<sprite> mainBody
    std::vector<<unique_ptrs<sprites>> components;
*/