#include <generated/systems/producer_systems/player_system.h>

#include <generated/components/basic_components/move_component.h>
#include <event/events/event_types/change_action_type_event.h>

#include <SFML/Window/Keyboard.hpp>
#include <generated/components/basic_components/basic_attack_needle_component.h>
#include <generated/components/data_components/boundary_component.h>
#include <generated/components/basic_components/projectile_component.h>
#include <generated/components/data_components/animation_player_component.h>
#include <generated/components/data_components/sprite_component.h>
#include <generated/components/data_components/elevation_level_component.h>
#include <generated/components/data_components/speed_component.h>
#include <generated/components/data_components/skin_component.h>

#include <utils/component_utils.h>
#include <entity_base/entity_handle.h>
void PlayerSystem::for_every_entity(
	EntityHandle entity,
	ActionTypeComponent& action_type,
	FacingSideComponent& facing_side,
    VelocityComponent& velocity,
	TransformComponent& transform){ 

	auto pos = sf::Mouse::getPosition(m_game_window.as_sfml_window());
	sf::Vector2f world_pos = m_game_window.as_sfml_window().mapPixelToCoords(pos);
	facing_side.side = transform.position.x < world_pos.x ? FacingSide::right : FacingSide::left;

	velocity.final_destination = transform.position;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { 
		auto projectile = m_game->create_entity();
		projectile.add_components(
			std::make_unique<SpeedComponent>(),
			std::make_unique<ProjectileComponent>());

		auto atk_transform = std::make_unique<TransformComponent>();

		atk_transform->position.x = transform.position.x;
		atk_transform->position.y = transform.position.y;
		atk_transform->scale = transform.scale;
		atk_transform->size.x = transform.size.x - 5;
		atk_transform->size.y = transform.size.y - 10;

		projectile.get_component<SpeedComponent>()->speed = 50.0f;
		projectile.add_components(std::move(atk_transform));
		
		auto projectile_sprite = std::make_unique<SpriteComponent>();
		projectile_sprite->sprite.setTexture(*ResourceManager::get_instance()->get_texture(Textures::ID::FIREBALL_1));
		projectile_sprite->sprite.setOrigin({projectile_sprite->sprite.getTextureRect().width / 2.0f,
		                                     projectile_sprite->sprite.getTextureRect().height / 2.0f});

		projectile.add_components(
			std::move(projectile_sprite),
			std::make_unique<ElevationLevelComponent>(ElevationLevel::two),
			std::make_unique<SkinComponent>(Skin::FIREBALL_1));

		

		projectile.add_components<BoundaryComponent>();

		auto target = std::make_unique<VelocityComponent>();
		target->final_destination = world_pos;
		projectile.add_components(std::move(target));

		return;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		ChangeActionTypeEvent{action_type, ActionType::idle}.happen();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		ChangeActionTypeEvent{action_type, ActionType::jump}.happen();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		ChangeActionTypeEvent{action_type, ActionType::attack}.happen();
		return;
	}

	ChangeActionTypeEvent{action_type, ActionType::move}.happen();
	// The magic number should be changed to be the end corners of the map (when boxed)
	// Apparently FLT_MIN == 0 ?!
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.final_destination.x += 100000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.final_destination.x -= 100000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) velocity.final_destination.y -= 100000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) velocity.final_destination.y += 100000.0f;
	entity.add_event_components<MoveComponent>();
}

