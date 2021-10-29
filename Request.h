#pragma once

#include "Message.h"
#include "IEncodable.h"
#include "IDecodable.h"
#include "RequestType.h"
#include <map>
#include "JSONNode.h"

class Request : public Message, public IDecodable
{
public:
	Request() {};

	// Inherited via IDecodable
	virtual void Decode(JSONObjectNode::Ptr node) override;

public:
	RequestType Type;
	JSONObjectNode::Ptr Data;
};

