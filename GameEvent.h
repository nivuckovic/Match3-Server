#pragma once

#include "Event.h"

template <typename TEvent>
class GameEvent : public Event
{
protected:
	virtual std::string GetEventType() override;
};

template<typename TEvent>
inline std::string GameEvent<TEvent>::GetEventType()
{
	return typeid(TEvent).name();
}
