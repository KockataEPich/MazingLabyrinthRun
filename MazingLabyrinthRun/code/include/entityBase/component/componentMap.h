#ifndef COMPONENT_SPRITE_MAP_HEADER_H
#define COMPONENT_SPRITE_MAP_HEADER_H

#include "../include/entityBase/component/componentSprite.h"

#include <functional>
#include <optional>
#include <unordered_map>

template<typename T>
class ComponentSpriteMap {
public:
	ComponentSpriteMap(std::function<void(std::unordered_map<T, std::optional<std::unique_ptr<ComponentSprite>>>)>
	                       populateComponentSpriteMap) {
		populateComponentSpriteMap(m_map);
	}

	void setComponentSprite(const T component, const std::optional<std::unique_ptr<ComponentSprite>>& componentSprite) {
		m_map[component] = std::move(componentSprite);
	}

	std::optional<ComponentSprite*> getComponentSprite(const T&) {
		auto component = m_map.at(T);
		return component->empty() ? std::nullopt : component.get()->get();
	}

private:
	std::unordered_map<T, std::optional<std::unique_ptr<ComponentSprite>>> m_map;
};

#endif