#include "../include/mobs/zombie/zombieLogic.h"

#include "../include/mobs/zombie/zombie_actions.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

ZombieLogic::ZombieLogic() {}

ZombieState* ZombieLogic::doLogic(const float deltaTime) {
	m_state.delta_time = deltaTime;

	std::vector<std::unique_ptr<Event>> all_actions;
	fill_actions_from_play_input(all_actions);
	for (auto& action : all_actions) { action->apply(); }

	return &m_state;
}

void ZombieLogic::initialize() {
	m_state.speed = 300.0f;
	m_sprite->setPosition(sf::Vector2f(0.0f, 0.0f));
	m_sprite->setOrigin(sf::Vector2f(m_sprite->getTexture()->getSize().x * m_sprite->getScale().x / 2.0f,
	                                 m_sprite->getTexture()->getSize().y * m_sprite->getScale().y / 2.0f));
	m_sprite->setScale(sf::Vector2f(6, 6));
	m_state.side = FacingSide::down;
}

void ZombieLogic::fill_actions_from_play_input(std::vector<std::unique_ptr<Event>>& actions) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		actions.push_back(std::make_unique<ZombieAttackEvent>(m_sprite, &m_state));

	if (actions.empty()) actions.push_back(std::make_unique<IdleAction>(m_sprite, &m_state));
}
