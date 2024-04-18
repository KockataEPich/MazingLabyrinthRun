#ifndef SYSTEM_UTILS_HEADER
#define SYSTEM_UTILS_HEADER

#include <entity_base/entity.h>
#include <component_base/component_mask.h>

#include <system/system.h>

inline void update_system_registration(const Entity entity,
									   ComponentMask new_mask,
									   ComponentMask old_mask,
									   EntityTrackerSystem* system) {
	ComponentMask systemSignature = system->get_signature();
	if (new_mask.is_new_match(old_mask, systemSignature))
		system->register_entity(entity);
	else if (new_mask.is_no_longer_matched(old_mask, systemSignature))
		system->unregister_entity(entity);
}

#endif