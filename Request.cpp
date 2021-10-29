#include "Request.h"

#include <ctime>
#include "TCPServer.h"
#include "EnumConverter.h"

void Request::Decode(JSONObjectNode::Ptr node)
{
	Identifier = node->GetValue<std::string>("identifier");
	Timestamp = node->GetValue<float>("timestamp");
	Type = static_cast<RequestType>(node->GetValue<int>("requestType"));
	Data = node->GetValue<JSONObjectNode::Ptr>("data");
}
