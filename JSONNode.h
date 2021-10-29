#pragma once
#include <string>
#include <memory>

class JSONObjectNode;

class JSONNode
{
public:
	typedef std::shared_ptr<JSONNode> Ptr;

	virtual std::string ToString() = 0;
};

