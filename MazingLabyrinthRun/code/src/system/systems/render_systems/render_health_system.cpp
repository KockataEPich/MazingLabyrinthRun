#include <generated/systems/render_systems/render_health_system.h>
#include <ui/health_bar.h>

void RenderHealthSystem::render() {
	for (auto& entity : m_registered_entities) {
		if (entity == m_game->player) continue; // Player has UI for this
		auto [transform, health_points] = m_game->components->unpack<TransformComponent, HealthPointsComponent>(entity);

		HealthBar health_bar;
		health_bar.initialize({transform->position.x - 30, transform->position.y - 60},
		                      {60, 10},
		                      health_points->health,
		                      health_points->max_health,
		                      false);

		m_game->window->draw(health_bar);
	}
}

void RenderHealthSystem::init() {}
