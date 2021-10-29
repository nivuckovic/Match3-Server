#include "JSONBoolNode.h"

JSONBoolNode::JSONBoolNode(bool value) : _value(value)
{
}

std::string JSONBoolNode::ToString()
{
    return _value ? "true" : "false";
}

bool JSONBoolNode::GetValue()
{
    return _value;
}
