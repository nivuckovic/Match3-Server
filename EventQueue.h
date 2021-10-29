#pragma once

#include <queue>
#include <string>
#include <map>
#include "GameEvents.h"
#include "GameEventSubscription.h"
#include "Logger.h"

class EventQueue
{
public:
	static void Update();

	static void CallEvent(Event::Ptr event);

	template<typename TEvent>
	static EventSubscription::Ptr SubscribeToEvent(std::function<void(std::shared_ptr<TEvent>)> callback);
	
	static void UnsubscribeFromEvent(EventSubscription::Ptr& eventSubscription);
private:
	EventQueue();

	static std::queue<Event::Ptr> _queue;
	// Mapa (event tip) - (ptri event subscriptiona)
	static std::map<std::string, std::vector<EventSubscription::Ptr>> _subscribers;
	static int _uniqueID;
};

// Pretplati se na event
// Kada se event pozove iz event queuea pozvat ce se odgovaraju callback na objektu
// koji se subscribeao
template <typename TEvent>
EventSubscription::Ptr EventQueue::SubscribeToEvent(std::function<void(std::shared_ptr<TEvent>)> callback)
{
	std::string className = typeid(TEvent).name();
	if(!_subscribers.count(className))
	{ 
		_subscribers[className] = std::vector<EventSubscription::Ptr>();
	}

	EventSubscription::Ptr result = std::make_shared<GameEventSubscription<TEvent>>(_uniqueID++, callback);
	_subscribers[className].push_back(result);
	return result;
}
