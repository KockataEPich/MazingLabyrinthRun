#include "../include/system/systems/player_system.h"

#include "../include/component_base/component_handle.h"
#include "../include/event/events/event_types/change_action_type_event.h"
#include "../include/event/events/event_types/move_event.h"

#include <SFML/Window/Keyboard.hpp>

void Player::update(float dt) {
	auto player = m_registered_entities[0];  // Only one player for the foreseeable future
	ComponentHandle<SpeedComponent> speed;
	ComponentHandle<FacingSideComponent> side;
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<ActionTypeComponent> action_type;
	ComponentHandle<CompositeEventComponent> events;

	m_parent_world->unpack(player, transform, side, speed, action_type, events);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		events->m_events->add_event(std::make_unique<ChangeActionTypeEvent>(*action_type.m_component, ActionType::idle));
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		events->m_events->add_event(std::make_unique<ChangeActionTypeEvent>(*action_type.m_component, ActionType::jump));
		return;
	}

	events->m_events->add_event(std::make_unique<ChangeActionTypeEvent>(*action_type.m_component, ActionType::move));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		events->m_events->add_event(std::make_unique<RunRight>(*transform.m_component, speed->m_speed, side->m_side));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		events->m_events->add_event(std::make_unique<RunLeft>(*transform.m_component, speed->m_speed, side->m_side));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		events->m_events->add_event(std::make_unique<RunUp>(*transform.m_component, speed->m_speed, side->m_side));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		events->m_events->add_event(std::make_unique<RunDown>(*transform.m_component, speed->m_speed, side->m_side));
}
