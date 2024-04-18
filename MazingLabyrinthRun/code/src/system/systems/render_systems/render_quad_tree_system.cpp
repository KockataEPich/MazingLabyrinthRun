#include <generated/systems/render_systems/render_quad_tree_system.h>
void RenderQuadTreeSystem::render(){ 
	render_full_quad_tree(*m_game->quad_tree);
}


void RenderQuadTreeSystem::render_full_quad_tree(QuadTree& quad_tree) {

	sf::RectangleShape rectangle({quad_tree.get_surface().width, quad_tree.get_surface().height});
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(6);
	rectangle.setOutlineColor(sf::Color::Blue);
	rectangle.setPosition({quad_tree.get_surface().left, quad_tree.get_surface().top});
	m_game->window->draw(rectangle);

	if (quad_tree.get_children())
		for (auto& child : quad_tree.get_children().value()) render_full_quad_tree(*child);
}