#include <system/systems/producer_systems/player_system.h>

#include <component_base/component_handle.h>
#include <event/events/event_types/change_action_type_event.h>

#include <SFML/Window/Keyboard.hpp>
#include <components/event_components/move_event_component.h>

void Player::update() {
	auto player = m_registered_entities[0];  // Only one player for the foreseeable future
	ComponentHandle<SpeedComponent> speed;
	ComponentHandle<FacingSideComponent> side;
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<ActionTypeComponent> action_type;
	ComponentHandle<TargetForDirection> target;

	m_parent_world->unpack(player, transform, side, speed, action_type, target);

	target->m_target_position = transform->m_position;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		ChangeActionTypeEvent{*action_type, ActionType::idle}.happen();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		ChangeActionTypeEvent{*action_type, ActionType::jump}.happen();
		return;
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		ChangeActionTypeEvent{*action_type, ActionType::attack}.happen();
		return;
	}

	ChangeActionTypeEvent{*action_type, ActionType::move}.happen();
	// The magic number should be changed to be the end corners of the map (when boxed)
	// Apparently FLT_MIN == 0 ?!
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) target->m_target_position.x += 100000.0f; 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) target->m_target_position.x -= 100000.0f; 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) target->m_target_position.y += 100000.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) target->m_target_position.y -= 100000.0f;
	m_parent_world->add_event_component(player, std::make_unique<MoveEventComponent>());
}
