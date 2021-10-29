#pragma once

#include "JSONObjectNode.h"

class IDecodable
{
public:
	virtual void Decode(JSONObjectNode::Ptr node) = 0;
};