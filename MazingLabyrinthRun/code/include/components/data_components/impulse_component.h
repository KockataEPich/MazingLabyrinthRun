#ifndef IMPULSE_COMPONENT_HEADER
#define IMPULSE_COMPONENT_HEADER

#include <component_base/component.h>
#include <attribute/impulse.h>

#include <optional>
struct ImpulseComponent : public Component<ImpulseComponent> {
	ImpulseComponent() = default;
	ImpulseComponent(ImpulseType impulse, std::optional<float> strength) : 
		m_impulse{impulse}
	,   m_strength{strength} {};
	ImpulseType m_impulse = ImpulseType::Move;
	std::optional<float> m_strength = std::nullopt;
};

#endif