#ifndef EVENT_BUS_HEADER
#	define EVENT_BUS_HEADER
#include <list>
#include <unordered_map>
#include <typeindex>

#include <event/member_function_handler.h>
#include <memory>

typedef std::list<std::unique_ptr<HandlerFunctionBase>> HandlerList;
class EventBus {
public:
	template<typename EventType>
	void publish(const Entity entity, EventType&& event) {
		std::type_index id = typeid(EventType);
		HandlerList* handlers = subscribers[id].get();

		if (!handlers) return;
		for (auto& handler : *handlers)
			if (handler) handler->exec(entity, std::move(event));
	}

	template<class T, class EventType>
	void subscribe(T* instance, void (T::*memberFunction)(const Entity, EventType&&)) {
		std::type_index id = typeid(EventType);
		if (!subscribers[id]) subscribers[id] = std::make_unique<HandlerList>();
		subscribers[id]->push_back(std::make_unique<MemberFunctionHandler<T, EventType>>(instance, memberFunction));
	}

private:
	std::unordered_map<std::type_index, std::unique_ptr<HandlerList>> subscribers;
};

#endif EVENT_BUS_HEADER