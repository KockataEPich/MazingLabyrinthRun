#include "../include/system/systems/player_system.h"

#include "../include/component_base/component_handle.h"

#include <SFML/Window/Keyboard.hpp>

void Player::update(float dt) {
	auto& player = m_registered_entities[0];  // Only one player for the foreseeable future
	ComponentHandle<SpeedComponent> speed;
	ComponentHandle<FacingSideComponent> side;
	ComponentHandle<TransformComponent> transform;
	ComponentHandle<ActionTypeComponent> action_type;

	m_parent_world->unpack(player, transform, side, speed, action_type);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		transform->m_position = {transform->m_position.x + (speed->m_speed * dt), transform->m_position.y};
		side->m_side = FacingSide::right;
		action_type->m_action_type = ActionType::move;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		transform->m_position = {transform->m_position.x - (speed->m_speed * dt), transform->m_position.y};
		side->m_side = FacingSide::left;
		action_type->m_action_type = ActionType::move;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		transform->m_position = {transform->m_position.x, transform->m_position.y - (speed->m_speed * dt)};
		side->m_side = FacingSide::up;
		action_type->m_action_type = ActionType::move;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		transform->m_position = {transform->m_position.x, transform->m_position.y + (speed->m_speed * dt)};
		side->m_side = FacingSide::down;
		action_type->m_action_type = ActionType::move;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) action_type->m_action_type = ActionType::jump;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
	    !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		action_type->m_action_type = ActionType::idle;
}