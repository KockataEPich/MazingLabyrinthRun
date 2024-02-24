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

	void update(float dt) { m_producer_system_sequence_wrapper.run_systems(dt); }
	void render() { for (auto& system : m_render_systems) system->render(); }

	void update_entity_system_subscriptions(const Entity, ComponentMask old_mask);
	void react_on_event(const Entity entity, ComponentMask new_mask);

	void remove_entity_from_systems(const Entity entity);

	template<class... ProducerSystem>
	void add_producer_systems(std::unique_ptr<ProducerSystem>&&... system) {
		([&] {
		  system->register_game(this->m_game);
	      m_producer_system_sequence_wrapper.add_system(std::move(system));
		}(),...);
	}

	template<class... ReactSystem>
	void add_react_systems(std::unique_ptr<ReactSystem>&&... system) {
		([&] {
			system->register_game(this->m_game);
			m_react_systems.push_back(std::move(system));
		}(), ...);
	}

	template<class... ImpulseSystem>
	void add_impulse_systems(std::unique_ptr<ImpulseSystem>&&... system) {
		([&] {
			system->register_game(this->m_game);
			m_impulse_systems.push_back(std::move(system));
		}(),...);
	}

	template<class... RenderSystem>
	void add_render_systems(std::unique_ptr<RenderSystem>&&... system) {
		([&] {
			system->register_game(this->m_game);
			m_render_systems.push_back(std::move(system));
		}(), ...);
	}

	void exchange_impulses(const Entity initiator, const Entity& victim, const CollisionInfo& collision_info);

private:
	std::vector<std::unique_ptr<ReactSystem>> m_react_systems;
	std::vector<std::unique_ptr<ImpulseSystem>> m_impulse_systems;
	std::vector<std::unique_ptr<RenderSystem>> m_render_systems;
	ProducerSystemSequenceWrapper m_producer_system_sequence_wrapper;

	Game* m_game;
};
#endif