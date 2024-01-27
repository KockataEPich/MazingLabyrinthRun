#ifndef WORLD_HEADER_H
#define WORLD_HEADER_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <any>
#include <memory>
#include <entity_base/entity.h>

class Game;
class World {
public:
	explicit World(Game* game) : m_game{game} {}

	void init();

	bool place_entity(const Entity entity, sf::Vector2f position);

	const sf::Sprite& get_player_sprite() { return *m_player_sprite; }

private:
	sf::Sprite* m_player_sprite;

	Game* m_game;
};
#endif