#ifndef HANDLER_FUNCTION_BASE_HEADER
#	define HANDLER_FUNCTION_BASE_HEADER

#include <event/event.h>

class HandlerFunctionBase {
public:
	void exec(Event&& event) { call(std::move(event)); }

private:
	virtual void call(Event&& event) = 0;
};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase {
public:
	typedef void (T::*MemberFunction)(EventType&&);

	MemberFunctionHandler(T* instance, MemberFunction memberFunction)
	    : instance{instance}
	    , memberFunction{memberFunction} {};

	void call(Event&& event) override{ 
		(instance->*memberFunction)((static_cast<EventType&&>(event)));
	}

private:
	T* instance;
	MemberFunction memberFunction;
};

#endif 