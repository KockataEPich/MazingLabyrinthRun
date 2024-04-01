#include <game.h>

#include <generated/components/data_components/boundary_component.h>
#include <utils/sfml_rect_helpers.h>

const int top_left = 0;
const int top_right = 1;
const int bottom_right = 2;
const int bottom_left = 3;

void QuadTree::insert(const Entity entity) {
	const sf::FloatRect& entity_position = std::get<0>(m_game->components->unpack<BoundaryComponent>(entity))->hitbox;
	insert(entity, entity_position);
}

void QuadTree::insert(const Entity entity, const sf::FloatRect& entity_hitbox) {
	if (!m_surface.intersects(entity_hitbox)) return;
	
	if (!m_children) {
		m_present_entities->insert(entity);
		split_if_needed();
		return;
	}

	for (auto& child : *m_children) child->insert(entity, entity_hitbox);
}

void QuadTree::remove(const Entity entity) {
	const sf::FloatRect& entity_position = std::get<0>(m_game->components->unpack<BoundaryComponent>(entity))->hitbox;
	remove(entity, entity_position);
}

void QuadTree::remove(const Entity entity, const sf::FloatRect& entity_box) {
	if (!m_surface.intersects(entity_box)) return;
	
	if (!m_children) {
		m_present_entities->erase(entity);
		return;
	}

	for (auto& child : *m_children) child->remove(entity, entity_box);
	merge_if_needed();
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

	for (auto entity : *m_present_entities) insert(entity);

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

	m_present_entities = std::set<Entity>();

	for (auto& child : *m_children) 
		for (auto entity : child->present_entities()) m_present_entities->insert(entity);

	m_children = std::nullopt;
}

std::set<Entity> QuadTree::get_potential_collisions(const sf::FloatRect& hitbox,
                                                       const sf::Vector2f& velocity) {

	sf::FloatRect expanded_hitbox = get_expanded_rectangle(hitbox, abs(velocity) * 2.4f);
	std::set<Entity> possible_collision_entities;

	gather_possible_collisions(possible_collision_entities, expanded_hitbox);

	return possible_collision_entities;
}

void QuadTree::gather_possible_collisions(std::set<Entity>& possible_collisions, sf::FloatRect& expanded_target) { 
	if (!m_children) {
		if (!m_surface.intersects(expanded_target)) return;
		possible_collisions.insert(present_entities().begin(), present_entities().end());
		return;
	}
	
	for (auto& child : *m_children) 
		child->gather_possible_collisions(possible_collisions, expanded_target);
}

void QuadTree::init() {}