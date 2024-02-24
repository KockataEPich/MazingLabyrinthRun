#ifndef QUAD_TREE_HEADER
#define QUAD_TREE_HEADER

#include <entity_base/entity.h>
#include <world/world.h>
#include <vector>
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
		m_present_entities = std::vector<Entity>();
	};

	void init();
	void insert(const Entity entity);
	void remove(const Entity entity);
	const std::vector<Entity>& get_neighbours(const Entity entity);

	bool has_space() { return m_present_entities->size() <= max_entities; }
	int number_of_present_entities() { return m_present_entities->size(); }
	std::vector<Entity>& present_entities() { return *m_present_entities; }
	std::optional<std::array<std::unique_ptr<QuadTree>, 4>>& get_children() { return m_children; }
	const sf::FloatRect& get_surface() { return m_surface; }

private: 
	const int max_entities = 12;
	const int max_layers = 5;
	int m_layer;

	std::optional<std::array<std::unique_ptr<QuadTree>, 4>> m_children;
	std::optional<std::vector<Entity>> m_present_entities;

	sf::FloatRect m_surface;
	Game* m_game;

	int determine_child(const Entity entity);
	void split_if_needed();
	void merge_if_needed();
};

#endif