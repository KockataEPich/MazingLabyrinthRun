#ifndef HANDLER_FUNCTION_BASE_HEADER
#	define HANDLER_FUNCTION_BASE_HEADER

#include <event/event.h>

class HandlerFunctionBase {
public:
	void exec(const Entity entity, Event&& event) { call(entity, std::move(event)); }

private:
	virtual void call(const Entity entity, Event&& event) = 0;
};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase {
public:
	typedef void (T::*MemberFunction)(const Entity, EventType&&);

	MemberFunctionHandler(T* instance, MemberFunction memberFunction)
	    : instance{instance}
	    , memberFunction{memberFunction} {};

	void call(const Entity entity, Event&& event) override { 
		(instance->*memberFunction)(entity, (static_cast<EventType&&>(event)));
	}

private:
	T* instance;
	MemberFunction memberFunction;
};

#endif 