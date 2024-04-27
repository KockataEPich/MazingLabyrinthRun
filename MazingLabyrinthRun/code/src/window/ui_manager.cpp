#include <ui/ui_manager.h>
#include <game.h>

#include <utils/sfml_vector_helpers.h>

#include <generated/components/data_components/health_points_component.h>

float position_health_bar(const float in, const float in2) { return in - in2 * 0.48f; }

void UIManager::update_ui() { 
	const auto& view = m_game->window->as_sfml_window().getView();
	m_player_health_bar.set_position(produce_x_and_y(view.getCenter(), view.getSize(), {position_health_bar}));

	auto player_hp = std::get<0>(m_game->components->unpack<HealthPointsComponent>(m_game->player));
	m_player_health_bar.set_health(player_hp->health, player_hp->max_health);
}

void UIManager::render_ui() { m_game->window->draw(m_player_health_bar); }

void UIManager::init() {
	auto player_hp = std::get<0>(m_game->components->unpack<HealthPointsComponent>(m_game->player));
	const auto& view = m_game->window->as_sfml_window().getView();

	m_player_health_bar.initialize(produce_x_and_y(view.getCenter(), view.getSize(), {position_health_bar}),
							       {200, 50},
							       player_hp->health,
							       player_hp->max_health,
							       true);
}