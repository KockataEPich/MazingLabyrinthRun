#ifndef I_VIEW_HEADER_H
#define I_VIEW_HEADER_H

#include "../complexWorldObject/active_object_state.h"
#include "../include/entityBase/complexWorldObject/borrowSpriteObject.h"
#include "../include/resource/skins.h"

#include <SFML/Graphics/Sprite.hpp>

template<typename T>
class IView : public BorrowSpriteObject {
public:
	IView(Skin&& start_skin) : m_skin{start_skin} {};
	virtual void update(const T* state, const float deltaTime) = 0;
	virtual void initialize() = 0;

protected:
	Skin m_skin;
};

#endif