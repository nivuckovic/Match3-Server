#pragma once

#include "JSONNode.h"

class JSONStringNode : public JSONNode
{
public:
	JSONStringNode(std::string value);

	std::string GetValue();

	virtual std::string ToString() override;

private:
	std::string _value;
};

