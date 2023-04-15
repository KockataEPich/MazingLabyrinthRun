#ifndef UPDATE_SOLID_SYSTEM_HEADER
#define UPDATE_SOLID_SYSTEM_HEADER

#include <components/data_components/sprite_component.h>
#include <components/data_components/transform_component.h>
#include <components/data_components/solid_component.h>
#include <components/event_components/update_solid_event_component.h>

#include <world/world.h>
#include <system/system.h>
class UpdateSolid : public ReactSystem {
public:
	UpdateSolid() {
		m_signature.add_component<TransformComponent>();
		m_signature.add_component<SolidComponent>();
		m_signature.add_component<UpdateSolidEventComponent>();
	}
	void react(const Entity& entity) override;
};

#endif