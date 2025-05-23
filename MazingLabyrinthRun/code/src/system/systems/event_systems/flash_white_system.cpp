#include <generated/systems/event_systems/flash_white_system.h>
void FlashWhiteSystem::p_handle_event(
        EntityHandle entity, 
    AnimationPlayerComponent& animation_player,
    SkinComponent& skin,
    FlashWhiteEvent& flash_white
    ){
	if(!animation_player.animation_player.is_flashed()) skin.skin = get_flashing_skin(skin.skin);
	animation_player.animation_player.flash_white();
}