#pragma once

#include "JSONNode.h"

class JSONIntegerNode : public JSONNode
{
public:
	JSONIntegerNode(int value);

	int GetValue();

	// Inherited via JSONNode
	virtual std::string ToString() override;
private:
	int _value;
};

