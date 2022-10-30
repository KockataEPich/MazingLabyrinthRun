#ifndef COMPONENT_INITIALIZER_HEADER
#define COMPONENT_INITIALIZER_HEADER

#include "../../entity_base/entity_handle.h"
class ComponentInitializer {
public:
	virtual void initialize_components(EntityHandle& entity) {};

protected:
	const sf::Vector2f m_default_scale = {6, 6};
};
#endif