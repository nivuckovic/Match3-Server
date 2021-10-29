#include "TestDecodable.h"
#include "Logger.h"

void TestDecodable::Decode(JSONObjectNode::Ptr node)
{
    _name = node->GetValue<std::string>("name");
    _level = node->GetValue<int>("level");
}

JSONNode::Ptr TestDecodable::Encode()
{
    JSONObjectNode::Ptr objectNode = std::make_shared<JSONObjectNode>();

    objectNode->AddValue("name", _name);
    objectNode->AddValue("level", _level);

    return objectNode;
}

std::string TestDecodable::GetName()
{
    return _name;
}

int TestDecodable::GetLevel()
{
    return _level;
}

