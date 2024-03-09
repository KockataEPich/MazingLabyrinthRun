#include <game.h>

#include <generated/components/data_components/boundary_component.h>

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
	if (number_entities_in_children > (max_entities * 3) * 0.25f) return;

	m_present_entities = std::vector<Entity>();

	for (auto& child : *m_children) 
		for (auto entity : child->present_entities()) m_present_entities->push_back(entity);

	m_children = std::nullopt;
}

int QuadTree::determine_child(const Entity entity) {
	const sf::Vector2f& entity_position = std::get<0>(m_game->components->unpack<BoundaryComponent>(entity))->hitbox.getPosition();
	return determine_child(entity_position);
}

int QuadTree::determine_child(const sf::Vector2f& entity_position) {
	if (entity_position.x < m_center.x && entity_position.y > m_center.y) return bottom_left;
	if (entity_position.x > m_center.x && entity_position.y > m_center.y) return bottom_right;
	if (entity_position.x > m_center.x && entity_position.y < m_center.y) return top_right;  
	if (entity_position.x < m_center.x && entity_position.y < m_center.y) return top_left;  

	// Edge cases
	if (entity_position.x == m_center.x && entity_position.y == m_center.y) return top_left; 
	if (entity_position.x < m_center.x && entity_position.y == m_center.y) return bottom_left;     
	if (entity_position.x == m_center.x && entity_position.y > m_center.y) return bottom_right;
	if (entity_position.x > m_center.x && entity_position.y == m_center.y) return top_right; 
	if (entity_position.x == m_center.x && entity_position.y < m_center.y) return top_left;
}

std::vector<Entity> QuadTree::get_potential_collisions(const sf::FloatRect& hitbox,
                                                       const sf::Vector2f& velocity) {
	sf::FloatRect expanded_hitbox{hitbox.left - std::abs(velocity.x),
	                              hitbox.top - std::abs(velocity.y),
	                              hitbox.width + std::abs(velocity.x) * 2,
	                              hitbox.height + std::abs(velocity.y) * 2};

	std::vector<Entity> possible_collision_entities;
	gather_possible_collisions(possible_collision_entities, expanded_hitbox);

	return possible_collision_entities;
}

void QuadTree::gather_possible_collisions(std::vector<Entity>& possible_collisions, sf::FloatRect& expanded_target) { 
	if (!m_children) {
		if (!m_surface.intersects(expanded_target)) return;
		sf::RectangleShape rectangle(m_surface.getSize());
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineThickness(8);
		rectangle.setOutlineColor(sf::Color::Yellow);
		rectangle.setPosition(m_surface.getPosition());
		m_game->m_window->draw(rectangle);
		possible_collisions.insert(possible_collisions.end(), present_entities().begin(), present_entities().end());
		return;
	}
	
	for (auto& child : *m_children) 
		child->gather_possible_collisions(possible_collisions, expanded_target);
}

void QuadTree::init() { 
	//auto all_entities = m_game->entities->get_all_alive_entities();
	//for (int entity : all_entities)
	//	insert(entity);
}