#include <ui/ui_manager.h>
#include <game.h>

#include <utils/sfml_vector_helpers.h>

#include <generated/components/data_components/health_points_component.h>

float position_health_bar(const float in, const float in2) { return in - in2 * 0.48f; }

void UIManager::update_ui() { 
	const auto& view = m_game->window->as_sfml_window().getView();
	m_health_bar.set_position(produce_x_and_y(view.getCenter(), view.getSize(), {position_health_bar}));

	auto player_hp = std::get<0>(m_game->components->unpack<HealthPointsComponent>(m_game->player));
	m_health_bar.set_health(player_hp->health, player_hp->max_health);

	m_ability_list.set_position(
	    {view.getCenter().x - view.getSize().x * 0.48f, view.getCenter().y - view.getSize().y * 0.41f});
	m_ability_list.update_cooldowns();
}

void UIManager::render_ui() {
	m_game->window->draw(m_health_bar); 
	m_game->window->draw(m_ability_list); 
}

void UIManager::init() {
	auto player_hp = std::get<0>(m_game->components->unpack<HealthPointsComponent>(m_game->player));
	const auto& view = m_game->window->as_sfml_window().getView();

	m_health_bar.initialize(produce_x_and_y(view.getCenter(), view.getSize(), {position_health_bar}),
						    {200, 50},
							player_hp->health,
							player_hp->max_health,
						    true);

	m_ability_list.initialize({50, 50});
}