#ifndef QUAD_TREE_HEADER
#define QUAD_TREE_HEADER

#include <entity_base/entity.h>
#include <world/world.h>
#include <vector>
#include <set>
#include <array>
#include <memory>
#include <optional>

class Game;
class QuadTree {
public:
	QuadTree(Game* game, sf::FloatRect surface, int layer) : 
		m_game{game}, 
		m_surface{surface}, 
		m_layer{layer}
	{
		m_present_entities = std::set<Entity>();
		m_center = {m_surface.left + m_surface.width * 0.5f, m_surface.top + m_surface.height * 0.5f};
	};

	void init();

	void insert(const Entity entity);
	void remove(const Entity entity);

	std::vector<Entity> get_potential_collisions(const sf::FloatRect& hitbox, const sf::Vector2f& velocity);
	const std::vector<Entity>& get_entities_residing_with_point(const sf::Vector2f& entity_position);

	bool has_space() { return m_present_entities->size() <= max_entities; }
	int number_of_present_entities() { return m_present_entities->size(); }
	std::set<Entity>& present_entities() { return *m_present_entities; }
	std::optional<std::array<std::unique_ptr<QuadTree>, 4>>& get_children() { return m_children; }
	const sf::FloatRect& get_surface() { return m_surface; }

private: 
	const int max_entities = 12;
	const int max_layers = 5;
	int m_layer;

	sf::Vector2f m_center;

	std::optional<std::array<std::unique_ptr<QuadTree>, 4>> m_children;
	std::optional<std::set<Entity>> m_present_entities;

	sf::FloatRect m_surface;
	Game* m_game;

	void insert(const Entity entity, const sf::FloatRect& entity_hitbox);
	void remove(const Entity entity, const sf::FloatRect& entity_hitbox);

	void split_if_needed();
	void merge_if_needed();

protected:
	void gather_possible_collisions(std::vector<Entity>& possible_collisions, sf::FloatRect& expanded_target);
};

#endif