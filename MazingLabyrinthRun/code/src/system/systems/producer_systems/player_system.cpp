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

	m_parent_world->unpack(player, transform, side, speed, action_type);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		ChangeActionTypeEvent{*action_type, ActionType::idle}.happen();
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		ChangeActionTypeEvent{*action_type, ActionType::jump}.happen();
		return;
	}

	ChangeActionTypeEvent{*action_type, ActionType::move}.happen();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) side->m_side = FacingSide::right;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) side->m_side = FacingSide::left;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) side->m_side = FacingSide::up;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) side->m_side = FacingSide::down;

	m_parent_world->add_event_component(player, std::make_unique<MoveEventComponent>());
}
