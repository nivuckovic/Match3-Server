#pragma once

#include "GameEvent.h"
#include <iostream>

class TestGE : public GameEvent<TestGE>
{
public:
	void Test()
	{
		std::cout << GetEventType();
	}
};

class Test2GE : public GameEvent<Test2GE>
{

};