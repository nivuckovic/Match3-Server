#include "EventQueue.h"
#include "Logger.h"

std::queue<Event::Ptr> EventQueue::_queue;
std::map<std::string, std::vector<EventSubscription::Ptr>> EventQueue::_subscribers;
int EventQueue::_uniqueID = 0;

void EventQueue::CallEvent(Event::Ptr event)
{
	_queue.push(std::static_pointer_cast<Event>(event));
}

void EventQueue::Update()
{
	while (!_queue.empty())
	{
		Event::Ptr nextEvent = _queue.front();
		_queue.pop();

		std::string className = nextEvent->GetEventType();
		if (_subscribers.count(className))
		{
			// Notify subscribers
			std::for_each(_subscribers[className].begin(), _subscribers[className].end(), [&nextEvent](EventSubscription::Ptr& eventSubscription) {
				eventSubscription->Callback(nextEvent);
			});
		}
	}
}

void EventQueue::UnsubscribeFromEvent(EventSubscription::Ptr& eventSubscription)
{
	int subscriptionID = eventSubscription->ID;
	std::string key = eventSubscription->GetEventType();
	
	if (_subscribers.count(key))
	{
		// Remove subscription from vector
		_subscribers[key].erase(
			std::remove_if(_subscribers[key].begin(), _subscribers[key].end(), [&subscriptionID](EventSubscription::Ptr x) {
			return subscriptionID == x->ID;
		}), _subscribers[key].end());
	}

	eventSubscription.reset();
}
