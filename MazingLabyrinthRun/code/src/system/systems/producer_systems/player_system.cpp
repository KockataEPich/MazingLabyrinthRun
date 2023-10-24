#include <generated/systems/producer_systems/player_system.h>

#include <generated/components/basic_components/move_component.h>
#include <event/events/event_types/change_action_type_event.h>

#include <SFML/Window/Keyboard.hpp>

void PlayerSystem::for_every_entity(
	Entity entity,
	ActionTypeComponent& action_type,
	FacingSideComponent& facing_side,
	TargetForDirectionComponent& target_for_direction,
	SpeedComponent& speed,
	TransformComponent& transform){ 

	target_for_direction.target_position = transform.position;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) target_for_direction.target_position.x += 100000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) target_for_direction.target_position.x -= 100000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) target_for_direction.target_position.y += 100000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) target_for_direction.target_position.y -= 100000.0f;
	m_parent_world->add_event_component(entity, std::make_unique<MoveComponent>());
}

