#pragma once

#include "Message.h"
#include "ResponseType.h"
#include "RequestType.h"
#include "IEncodable.h"
#include "JSONObjectNode.h"

class Response : public Message, public IEncodable
{
public:
	static Response CreateResponse(ResponseType type, std::string requestIdentifier, JSONObjectNode::Ptr data);

	// Inherited via IEncodable
	virtual JSONNode::Ptr Encode() override;

public:
	ResponseType Type;
	std::string ResponseToIdentifier;
	JSONObjectNode::Ptr Data;
private:
	Response(ResponseType type, std::string requestIdentifier, JSONObjectNode::Ptr data);
};

