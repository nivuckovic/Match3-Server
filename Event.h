#pragma once

#include <memory>
#include <string>

class Event
{
public:
	typedef std::shared_ptr<Event> Ptr;

	virtual std::string GetEventType() = 0;
};

