#include "Response.h"
#include "JSONObjectNode.h"
#include <ctime>
#include "TCPServer.h"

Response::Response(ResponseType type, std::string requestIdentifier, JSONObjectNode::Ptr data)
{
	Identifier = TCPServer::CreateUUID();
	Timestamp = time(0);
	ResponseToIdentifier = requestIdentifier;
	Type = type;
	Data = data;
}

Response Response::CreateResponse(ResponseType type, std::string requestIdentifier, JSONObjectNode::Ptr data)
{
	Response response(type, requestIdentifier, data);
	return response;
}

JSONNode::Ptr Response::Encode()
{
	JSONObjectNode::Ptr node = std::make_shared<JSONObjectNode>();

	node->AddValue<int>("responseType", static_cast<int>(Type));
	node->AddValue<std::string>("identifier", Identifier);
	node->AddValue<std::string>("responseTo", ResponseToIdentifier);
	node->AddValue<float>("timestamp", Timestamp);
	node->AddValue<JSONObjectNode::Ptr>("data", Data);

	return node;
}
