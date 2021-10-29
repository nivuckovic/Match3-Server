#include "JSONObjectNode.h"

JSONObjectNode::JSONObjectNode(std::map<std::string, std::shared_ptr<JSONNode>> table) : _table(table) {};

std::string JSONObjectNode::ToString()
{
	std::string result = "{";

	for (auto &pair : _table)
	{
		result += "\"" + pair.first + "\" : " + (pair.second == nullptr ? "{}" : pair.second->ToString()) + ", ";
	}

	return result + "}";
}

void JSONObjectNode::CheckTableContainsKey(std::string key)
{
	try {
		if (_table.find(key) == _table.end())
			throw std::exception(("Key(" + key + ") ne postoji!").c_str());
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}
