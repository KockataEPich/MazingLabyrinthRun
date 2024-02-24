#include <world/quad_tree.h>
#include <game.h>

#include <generated/components/data_components/transform_component.h>

const int top_left = 0;
const int top_right = 1;
const int bottom_right = 2;
const int bottom_left = 3;

void QuadTree::insert(const Entity entity) {
	split_if_needed();
	if (m_children) {
		m_children->at(determine_child(entity))->insert(entity); 
		return;
	}

	m_present_entities->push_back(entity);
}

void QuadTree::remove(const Entity entity) {
	if (m_children) {
		m_children->at(determine_child(entity))->remove(entity);
		merge_if_needed();
		return;
	}

	std::erase(*m_present_entities, entity); 
}

void QuadTree::split_if_needed() { 
	if (m_layer == max_layers) return;
	if (m_children) return;
	if (has_space()) return; 

	m_children = std::to_array<std::unique_ptr<QuadTree>, 4>({nullptr, nullptr, nullptr, nullptr});
	auto set_rect_at_index = [&](float left, float top, int index) {
		m_children->at(index) =
		    std::make_unique<QuadTree>(m_game, sf::FloatRect(left, top, m_surface.width * 0.5f, m_surface.height * 0.5f), m_layer + 1);
	};

	set_rect_at_index(m_surface.left, m_surface.top, 0);
	set_rect_at_index(m_surface.left + m_surface.width * 0.5f, m_surface.top, 1);
	set_rect_at_index(m_surface.left + m_surface.width * 0.5f, m_surface.top + m_surface.height * 0.5f, 2);
	set_rect_at_index(m_surface.left, m_surface.top + m_surface.height * 0.5f, 3);

	for (auto entity : *m_present_entities) m_children->at(determine_child(entity))->insert(entity);

	m_present_entities = std::nullopt;
}

void QuadTree::merge_if_needed() {
	int number_entities_in_children = 0;
	for (auto& child : *m_children) { 
		if (child->get_children()) return;
		number_entities_in_children += child->number_of_present_entities(); 
	}

	// As I don't really want for constant merging and unmerging near the max, there is a bit of a tolerance.
	if (number_entities_in_children < (max_entities * 3) / 4) return;

	m_present_entities = std::vector<Entity>();

	for (auto& child : *m_children) 
		for (auto entity : child->present_entities()) m_present_entities->push_back(entity);

	m_children = std::nullopt;
}

int QuadTree::determine_child(const Entity entity) {
	const sf::Vector2f& entity_position = std::get<0>(m_game->components->unpack<TransformComponent>(entity))->position;
	sf::Vector2f center = {m_surface.left + m_surface.width * 0.5f, m_surface.top + m_surface.height * 0.5f};

	if (entity_position.x < center.x && entity_position.y > center.y) return bottom_left;
	if (entity_position.x > center.x && entity_position.y > center.y) return bottom_right;
	if (entity_position.x > center.x && entity_position.y < center.y) return top_right;  
	if (entity_position.x < center.x && entity_position.y < center.y) return top_left;  

	// Edge cases
	if (entity_position.x == center.x && entity_position.y == center.y) return top_left; 
	if (entity_position.x < center.x && entity_position.y == center.y) return bottom_left;     
	if (entity_position.x == center.x && entity_position.y > center.y) return bottom_right;
	if (entity_position.x > center.x && entity_position.y == center.y) return top_right; 
	if (entity_position.x == center.x && entity_position.y < center.y) return top_left;
}

const std::vector<Entity>& QuadTree::get_neighbours(const Entity entity) {
	if (m_children) return m_children->at(determine_child(entity))->get_neighbours(entity);
	return present_entities();
}

void QuadTree::init() { 
	auto all_entities = m_game->entities->get_all_alive_entities();
	for (int entity : all_entities)
		insert(entity);
}