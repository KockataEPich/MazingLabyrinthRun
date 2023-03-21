#ifndef SYSTEM_SEQUENCE_WRAPPER_HEADER
#define SYSTEM_SEQUENCE_WRAPPER_HEADER

#include "../component_base/component_mask.h"
#include "../entity_base/entity.h"
#include "system.h"
#include <bitset>
#include <vector>
#include <memory>

const float base_system_tick_frequency = 0.015; // Acquired through testing for smooth feeling

class World;

inline int get_amount_of_tickts_to_execute(float dt) {

}

class SystemSequenceWrapper {
public:
	void add_system(System* system) { m_system_list.push_back(system); }
	void run_systems(float dt) {
		int ticks_to_execute = get_ticks(dt);
		while (ticks_to_execute != 0) {
			for (auto& system : m_system_list) { system->work(); }
			ticks_to_execute--;
		}
	}

private:
	std::vector<System*> m_system_list;
	float m_delta_accumulator = 0;

	int get_ticks(float dt) {
		m_delta_accumulator += dt;
		int ticks_to_execute = 0;

		while (m_delta_accumulator >= base_system_tick_frequency) {
			m_delta_accumulator -= base_system_tick_frequency;
			ticks_to_execute++;
		}

		return ticks_to_execute;
	}
};
#endif
