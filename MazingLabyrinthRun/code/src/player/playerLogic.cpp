#include "../include/player/playerLogic.h"

#include "../include/player/player_actions.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

PlayerLogic::PlayerLogic() {}

PlayerState* PlayerLogic::doLogic(const float deltaTime) {
	m_state.delta_time = deltaTime;

	std::vector<std::unique_ptr<Action>> all_actions;
	fill_actions_from_play_input(all_actions);
	for (auto& action : all_actions) { action->apply(); }

	return &m_state;
}

void PlayerLogic::initialize() {
	m_state.speed = 300.0f;
	m_sprite->setPosition(sf::Vector2f(0.0f, 0.0f));
	m_sprite->setOrigin(sf::Vector2f(m_sprite->getTexture()->getSize().x * m_sprite->getScale().x / 2.0f,
	                                 m_sprite->getTexture()->getSize().y * m_sprite->getScale().y / 2.0f));
	m_sprite->setScale(sf::Vector2f(6, 6));
	m_state.side = FacingSide::down;
}

void PlayerLogic::fill_actions_from_play_input(std::vector<std::unique_ptr<Action>>& actions) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		actions.push_back(std::make_unique<MoveRight>(&m_state, m_sprite));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		actions.push_back(std::make_unique<MoveLeft>(&m_state, m_sprite));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		actions.push_back(std::make_unique<MoveUp>(&m_state, m_sprite));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		actions.push_back(std::make_unique<MoveDown>(&m_state, m_sprite));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		actions.push_back(std::make_unique<JumpAction>(&m_state, m_sprite));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
	    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		actions.push_back(std::make_unique<RunAction>(&m_state, m_sprite));

	if (actions.empty()) actions.push_back(std::make_unique<IdleAction>(&m_state, m_sprite));
}
