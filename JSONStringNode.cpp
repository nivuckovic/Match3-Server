#include "JSONStringNode.h"

JSONStringNode::JSONStringNode(std::string value) : _value(value) {}

std::string JSONStringNode::GetValue()
{
	return _value;
}

std::string JSONStringNode::ToString()
{
	return "\"" + _value + "\"";
}
