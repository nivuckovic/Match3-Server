#pragma once

#include "IDecodable.h"
#include "IEncodable.h"

class TestDecodable : public IDecodable, public IEncodable
{
public:
	// Inherited via IDecodable
	virtual void Decode(JSONObjectNode::Ptr node) override;

	// Inherited via IEncodable
	virtual JSONNode::Ptr Encode() override;

	std::string GetName();
	int GetLevel();

private:
	std::string _name;
	int _level;
};

