#include <generated/systems/react_systems/flash_white_system.h>
void FlashWhiteSystem::react_on_entity(
        EntityHandle entity, 
    AnimationPlayerComponent& animation_player,
    SkinComponent& skin
    ){
	if(!animation_player.animation_player.is_flashed()) skin.skin = get_flashing_skin(skin.skin);
	animation_player.animation_player.flash_white();
}