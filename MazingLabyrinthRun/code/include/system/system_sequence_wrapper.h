#ifndef SYSTEM_SEQUENCE_WRAPPER_HEADER
#define SYSTEM_SEQUENCE_WRAPPER_HEADER

#include "../component_base/component_mask.h"
#include "../entity_base/entity.h"
#include "system.h"
#include <bitset>
#include <vector>
#include <memory>

#include <system/system_utils.h>
const float base_system_tick_frequency = 0.015; // Acquired through testing for smooth feeling

class ProducerSystemSequenceWrapper {
public:
	void add_system(std::unique_ptr<ProducerSystem>&& system) { m_system_list.push_back(std::move(system)); }

	void add_non_tick_system(std::unique_ptr<ProducerSystem>&& system) {
		m_non_ticks_system_list.push_back(std::move(system));
	}

	void run_systems(float dt) {
		for (auto& system : m_non_ticks_system_list) system->update();

		int ticks_to_execute = get_ticks(dt);
		while (ticks_to_execute != 0) {
			for (auto& system : m_system_list) system->update_in_ticks();
			ticks_to_execute--;
		}
	}

	void init() { 
		for (auto& system : m_system_list) system->init();
		for (auto& system : m_non_ticks_system_list) system->init();
	}

	void update_systems_registrations(const Entity entity, ComponentMask new_mask, ComponentMask old_mask) {
		for (auto& system : m_system_list) 
			update_system_registration(entity, new_mask, old_mask, system.get());
		for (auto& system : m_non_ticks_system_list) 
			update_system_registration(entity, new_mask, old_mask, system.get());
	}

	void remove_entity_from_systems(const Entity entity, ComponentMask mask) {
		for (auto& system : m_system_list) 
			if (mask.matches(system->get_signature())) system->unregister_entity(entity);

		for (auto& system : m_non_ticks_system_list)
			if (mask.matches(system->get_signature())) system->unregister_entity(entity);
	}


private:
	std::vector<std::unique_ptr<ProducerSystem>> m_system_list;
	std::vector<std::unique_ptr<ProducerSystem>> m_non_ticks_system_list;
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
