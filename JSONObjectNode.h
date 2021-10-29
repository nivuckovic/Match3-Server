#pragma once

#include "JSONNode.h"
#include "JSONStringNode.h"
#include "JSONBoolNode.h"
#include "JSONFloatNode.h"
#include "JSONIntegerNode.h"
#include "JSONVectorNode.h"

#include <map>
#include <memory>
#include <iostream>

class JSONObjectNode : public JSONNode
{
public:
	typedef std::shared_ptr<JSONObjectNode> Ptr;

	JSONObjectNode() {};
	JSONObjectNode(std::map<std::string, std::shared_ptr<JSONNode>> table);

	template<typename T>
	T GetValue(std::string key);

	template <>
	std::string GetValue<std::string>(std::string key);

	template<>
	bool GetValue<bool>(std::string key);

	template<>
	float GetValue<float>(std::string key);

	template<>
	int GetValue<int>(std::string key);

	template<>
	std::vector<int> GetValue<std::vector<int>>(std::string key);

	template<>
	JSONObjectNode GetValue<JSONObjectNode>(std::string key);

	template<typename T>
	void AddValue(std::string key, T value);

	template<>
	void AddValue<int>(std::string key, int value);

	template<>
	void AddValue<float>(std::string key, float value);

	template<>
	void AddValue<std::string>(std::string key, std::string value);

	template<>
	void AddValue<JSONObjectNode::Ptr>(std::string key, JSONObjectNode::Ptr value);

	template<>
	void AddValue<JSONNode::Ptr>(std::string key, JSONNode::Ptr value);

	template<>
	void AddValue<std::vector<int>>(std::string key, std::vector<int> value);

	virtual std::string ToString() override;
private:
	void CheckTableContainsKey(std::string key);

	std::map<std::string, JSONNode::Ptr> _table;
};

template<>
inline std::vector<int> JSONObjectNode::GetValue(std::string key)
{
	CheckTableContainsKey(key);

	return std::static_pointer_cast<JSONVectorNode<int>>(_table[key])->GetValue();
}

template<>
inline std::string JSONObjectNode::GetValue<std::string>(std::string key)
{
	CheckTableContainsKey(key);

	return std::static_pointer_cast<JSONStringNode>(_table[key])->GetValue();
}

template<>
inline bool JSONObjectNode::GetValue<bool>(std::string key)
{
	CheckTableContainsKey(key);

	return std::static_pointer_cast<JSONBoolNode>(_table[key])->GetValue();
}

template<>
inline float JSONObjectNode::GetValue<float>(std::string key)
{
	CheckTableContainsKey(key);

	return std::static_pointer_cast<JSONFloatNode>(_table[key])->GetValue();
}

template<>
inline int JSONObjectNode::GetValue<int>(std::string key)
{
	CheckTableContainsKey(key);

	return std::static_pointer_cast<JSONIntegerNode>(_table[key])->GetValue();
}

template<>
inline JSONObjectNode::Ptr JSONObjectNode::GetValue<JSONObjectNode::Ptr>(std::string key)
{
	CheckTableContainsKey(key);

	return std::static_pointer_cast<JSONObjectNode>(_table[key]);
}

template<>
inline void JSONObjectNode::AddValue<int>(std::string key, int value)
{
	_table[key] = std::make_shared<JSONIntegerNode>(value);
}

template<>
inline void JSONObjectNode::AddValue(std::string key, float value)
{
	_table[key] = std::make_shared<JSONFloatNode>(value);
}

template<>
inline void JSONObjectNode::AddValue<std::string>(std::string key, std::string value)
{
	_table[key] = std::make_shared<JSONStringNode>(value);
}

template<>
inline void JSONObjectNode::AddValue<JSONObjectNode::Ptr>(std::string key, JSONObjectNode::Ptr value)
{
	_table[key] = value;
}

template<>
inline void JSONObjectNode::AddValue<JSONNode::Ptr>(std::string key, JSONNode::Ptr value)
{
	_table[key] = value;
}

template<>
inline void JSONObjectNode::AddValue<std::vector<int>>(std::string key, std::vector<int> value)
{
	_table[key] = std::make_shared<JSONVectorNode<int>>(value);
}