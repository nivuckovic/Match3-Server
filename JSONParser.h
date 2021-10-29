#pragma once
#include <sstream>
#include "Logger.h"
#include "JSONNode.h"
#include "JSONTokens.h"
#include <vector>
#include <queue>
#include <functional>
#include "JSONVectorNode.h"
#include "JSONObjectNode.h"

class JSONParser
{
public:
	static JSONParser& GetInstance();
	
	JSONObjectNode::Ptr Decode(std::string s);
	JSONNode::Ptr Decode(std::stringstream& ss);
	std::string Encode(JSONNode::Ptr node);

private:
	JSONParser() {};

	std::queue<JSON::Token> Tokenize(std::stringstream& ss);
	JSONNode::Ptr CreateJSONNodeTree(std::queue<JSON::Token>& tokens);

	JSONNode::Ptr CreateJSONObjectNode(std::queue<JSON::Token>& tokens);
	JSONNode::Ptr CreateJSONStringNode(JSON::Token& token);
	JSONNode::Ptr CreateJSONBoolNode(JSON::Token& token);
	JSONNode::Ptr CreateJSONNumericNode(JSON::Token& token);
	JSONNode::Ptr CreateJSONIntegerNode(JSON::Token& token);
	JSONNode::Ptr CreateJSONFloatNode(JSON::Token& token);
	JSONNode::Ptr CreateJSONListNode(std::queue<JSON::Token>& tokens);

	template<typename T>
	JSONNode::Ptr CreateJSONListNode(std::queue<JSON::Token>& tokens, JSON::TokenType expectedToken, std::function<T(std::string)> valueExtractor);

	JSON::Token GetNextToken(std::queue<JSON::Token>& tokens, std::initializer_list<JSON::TokenType> expectedTokens);
	JSON::Token PeekNextToken(std::queue<JSON::Token>& tokens, std::initializer_list<JSON::TokenType> expectedTokens);

	void CheckTokenType(JSON::TokenType type, std::initializer_list<JSON::TokenType> expectedTokens);
};

template<typename T>
inline JSONNode::Ptr JSONParser::CreateJSONListNode(std::queue<JSON::Token>& tokens, JSON::TokenType expectedToken, std::function<T(std::string)> valueExtractor)
{
	std::vector<T> result;

	while (true)
	{
		JSON::Token nextToken = GetNextToken(tokens, { expectedToken, JSON::TokenType::ListEnd });
		if (nextToken.Type == JSON::TokenType::ListEnd)
			break;

		result.push_back(valueExtractor(nextToken.Value));

		nextToken = GetNextToken(tokens, { JSON::TokenType::Comma, JSON::TokenType::ListEnd });
		if (nextToken.Type == JSON::TokenType::ListEnd)
			break;
	}

	return std::make_shared<JSONVectorNode<T>>(result);
}
