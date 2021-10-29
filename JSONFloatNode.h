#pragma once

#include "JSONNode.h"

class JSONFloatNode : public JSONNode
{
public:
	JSONFloatNode(float value);

	float GetValue();

	// Inherited via JSONNode
	virtual std::string ToString() override;

private:
	float _value;
};

