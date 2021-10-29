#pragma once

#include "JSONNode.h"

class JSONBoolNode : public JSONNode
{
public:
	JSONBoolNode(bool value);

	virtual std::string ToString() override;

	bool GetValue();

private:
	bool _value;
};

