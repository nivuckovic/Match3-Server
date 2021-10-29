#pragma once

#include <functional>
#include "Event.h"

class EventSubscription
{
public:
	typedef std::shared_ptr<EventSubscription> Ptr;

	virtual void Callback(Event::Ptr event) = 0;
	virtual std::string GetEventType() = 0;

	const int ID;

protected:
	EventSubscription(int id) : ID(id) {};
};

