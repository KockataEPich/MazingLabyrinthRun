#ifndef ACTIVE_OBJECT_HEADER_H
#define ACTIVE_OBJECT_HEADER_H

#include "../include/entityBase/logic/iLogic.h"
#include "../include/entityBase/view/iView.h"
#include "../include/entityBase/worldObject.h"

#include <memory>

template<typename T>
class ActiveObject : public virtual WorldObject {
public:
	ActiveObject(std::unique_ptr<ILogic<T>> logic, std::unique_ptr<IView<T>> view)
	    : WorldObject()
	    , m_logic(std::move(logic))
	    , m_view(std::move(view)) {
		setSpritesOfComponents();
	}
	void play(const float deltaTime);

private:
	std::unique_ptr<ILogic<T>> m_logic;
	std::unique_ptr<IView<T>> m_view;

	void setSpritesOfComponents() {
		m_view->setSprite(m_sprite.get());
		m_logic->setSprite(m_sprite.get());

		m_view->initialize();
		m_logic->initialize();
	};
};

template<typename T>
void ActiveObject<T>::play(const float deltaTime) {
	T* state = m_logic->doLogic(deltaTime);
	m_view->update(state, deltaTime);
}

#endif