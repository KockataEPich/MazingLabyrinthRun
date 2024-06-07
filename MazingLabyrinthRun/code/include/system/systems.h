#ifndef SYSTEMS_HEADER
#define SYSTEMS_HEADER

#include "system.h"
#include "system_sequence_wrapper.h"

#include <memory>
#include <tuple>
#include <functional>
#include <utils/collision_utils.h>

class Game;
class Systems {
public:
	explicit Systems(Game* game) : m_game{game} {}

	void init();

	void update(float dt) { m_producer_systems.run_systems(dt); }
	void render() { for (auto& system : m_render_systems) system->render(); }

	void update_entity_system_subscriptions(const Entity, ComponentMask old_mask);
	void remove_entity_from_systems(const Entity entity);
	
	template<typename... System>
	void add_systems(std::unique_ptr<System>&&... system) {
		([&] {
			system->register_game(this->m_game);
			if constexpr (std::is_base_of_v<ProducerSystem, System>) {
				m_producer_systems.add_system(std::move(system));
			}
			if constexpr (std::is_base_of_v<ImpulseSystem, System>) {
				m_impulse_systems.push_back(std::move(system));
			}
			if constexpr (std::is_base_of_v<RenderSystem, System>) {
			    m_render_systems.push_back(std::move(system));
			}
			if constexpr (!std::is_base_of_v<ProducerSystem, System> &&
						  !std::is_base_of_v<ImpulseSystem, System> &&
			              !std::is_base_of_v<RenderSystem, System>) {
				m_event_systems.push_back(std::move(system));
			}
		}(), ...);
	}
	void exchange_impulses(const Entity initiator, const Entity& victim, const CollisionInfo& collision_info);

private:
	std::vector<std::unique_ptr<System>> m_event_systems;
	std::vector<std::unique_ptr<ImpulseSystem>> m_impulse_systems;
	std::vector<std::unique_ptr<RenderSystem>> m_render_systems;
	ProducerSystemSequenceWrapper m_producer_systems;

	Game* m_game;
};
#endif