#pragma once

#include "EventSubscription.h"
#include <functional>

template<typename TEvent>
class GameEventSubscription : public EventSubscription
{
public:
	GameEventSubscription(int id, std::function<void(std::shared_ptr<TEvent>)> callback) : EventSubscription(id), _callback(callback) {};

	// Inherited via EventSubscription
	virtual void Callback(Event::Ptr event) override;
	// Inherited via EventSubscription
	virtual std::string GetEventType() override;

private:
	std::function<void(std::shared_ptr<TEvent>)> _callback;
};

template<typename TEvent>
inline void GameEventSubscription<TEvent>::Callback(Event::Ptr event)
{
	_callback(std::static_pointer_cast<TEvent>(event));
}

template<typename TEvent>
inline std::string GameEventSubscription<TEvent>::GetEventType()
{
	return typeid(TEvent).name();
}
