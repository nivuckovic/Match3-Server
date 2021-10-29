#pragma once
#include <string>

#include "JSONNode.h"

class IEncodable
{
public:
	virtual JSONNode::Ptr Encode() = 0;
};