#include "JSONParser.h"
#include <algorithm>
#include <map>
#include "JSONObjectNode.h"
#include "JSONBoolNode.h"
#include <format>

JSONParser& JSONParser::GetInstance()
{
	static JSONParser instance;
	return instance;
}

JSONNode::Ptr JSONParser::Decode(std::stringstream& ss)
{
	std::queue<JSON::Token> tokens = Tokenize(ss);
	return CreateJSONNodeTree(tokens);
}

JSONObjectNode::Ptr JSONParser::Decode(std::string s)
{
	std::stringstream ss(s);
	return std::static_pointer_cast<JSONObjectNode>(Decode(ss));
}

std::string JSONParser::Encode(JSONNode::Ptr node)
{
	return node->ToString();
}

std::queue<JSON::Token> JSONParser::Tokenize(std::stringstream& ss)
{
	std::queue<JSON::Token> result;

	while (!ss.eof())
	{
		bool invalidChar = true;
		if (ss.peek() == ' ' || ss.peek() == -1)
		{
			ss.get();
			continue;
		}

		switch (ss.peek())
		{
		case '{':
			result.push(JSON::Token(JSON::TokenType::ObjectStart, "{"));
			ss.get();
			invalidChar = false;
			break;
		case '}':
			result.push(JSON::Token(JSON::TokenType::ObjectEnd, "}"));
			ss.get();
			invalidChar = false;
			break;
		case ':':
			result.push(JSON::Token(JSON::TokenType::Colon, ":"));
			ss.get();
			invalidChar = false;
			break;
		case ',':
			result.push(JSON::Token(JSON::TokenType::Comma, ","));
			ss.get();
			invalidChar = false;
			break;
		case '[':
			result.push(JSON::Token(JSON::TokenType::ListStart, "["));
			ss.get();
			invalidChar = false;
			break;
		case ']':
			result.push(JSON::Token(JSON::TokenType::ListEnd, "]"));
			ss.get();
			invalidChar = false;
			break;
		case '\"':
			ss.get();
			invalidChar = false;

			std::string value;
			getline(ss, value, '\"');

			result.push(JSON::Token(JSON::TokenType::String, value));
			break;
		}

		if (isdigit(ss.peek())) {
			std::string value;
			
			while (isdigit(ss.peek()) || ss.peek() == '.')
			{
				value += ss.get();
			}

			int counter = 0;
			auto predicate = [&counter](char c) {
				if (c == '.')
					++counter;

				if (counter > 1)
					return false;

				return isdigit(c) || c == '.';
			};

			if (std::all_of(value.begin(), value.end(), predicate) && value.back() != '.')
			{
				invalidChar = false;
				result.push(JSON::Token(JSON::TokenType::Number, value));
			}
		}

		if (isalpha(ss.peek()))
		{
			std::string value;
			while (isalpha(ss.peek()))
			{
				value += ss.get();
			}

			if(value == "true" || value == "false")
			{ 
				invalidChar = false;
				result.push(JSON::Token(JSON::TokenType::Bool, value));
			}
		}

		if (invalidChar)
		{
			result.push(JSON::Token(JSON::TokenType::Invalid, std::to_string(ss.get())));
		}
	}

	return result;
}

JSONNode::Ptr JSONParser::CreateJSONNodeTree(std::queue<JSON::Token>& tokens)
{
	GetNextToken(tokens, { JSON::TokenType::ObjectStart });

	return CreateJSONObjectNode(tokens);
}

JSON::Token JSONParser::GetNextToken(std::queue<JSON::Token>& tokens, std::initializer_list<JSON::TokenType> expectedTokens)
{
	JSON::Token result = tokens.front();
	tokens.pop();

	CheckTokenType(result.Type, expectedTokens);

	return result;
}

JSON::Token JSONParser::PeekNextToken(std::queue<JSON::Token>& tokens, std::initializer_list<JSON::TokenType> expectedTokens)
{
	JSON::Token result = tokens.front();

	CheckTokenType(result.Type, expectedTokens);

	return tokens.front();
}

void JSONParser::CheckTokenType(JSON::TokenType type, std::initializer_list<JSON::TokenType> expectedTokens)
{
	auto predicate = [&type](JSON::TokenType expectedType) { return type == expectedType; };
	try
	{
		if (!std::any_of(expectedTokens.begin(), expectedTokens.end(), predicate))
		{
			std::string expectedTokensMsg;
			std::for_each(expectedTokens.begin(), expectedTokens.end(), [&expectedTokensMsg, &type](JSON::TokenType type)
			{
				expectedTokensMsg += JSON::TypeToString(type) + ", ";
			});


			std::string msg = "Neispravan token! Ocekivani: " + expectedTokensMsg + "dobiven: " + JSON::TypeToString(type);
			throw std::exception(msg.c_str());
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

JSONNode::Ptr JSONParser::CreateJSONObjectNode(std::queue<JSON::Token>& tokens)
{
	std::map<std::string, JSONNode::Ptr> table;

	while (true)
	{
		JSON::Token nextToken = GetNextToken(tokens, { JSON::TokenType::String, JSON::TokenType::ObjectEnd });
		if (nextToken.Type == JSON::TokenType::ObjectEnd)
			break;

		std::string key = nextToken.Value;
		GetNextToken(tokens, { JSON::TokenType::Colon });

		nextToken = GetNextToken(tokens, { JSON::TokenType::Bool, JSON::TokenType::String, JSON::TokenType::Number, JSON::TokenType::ObjectStart, JSON::TokenType::ListStart});
		switch (nextToken.Type)
		{
			case JSON::TokenType::Bool:
				table[key] = CreateJSONBoolNode(nextToken);
				break;

			case JSON::TokenType::String:
				table[key] = CreateJSONStringNode(nextToken);
				break;

			case JSON::TokenType::Number:
				table[key] = CreateJSONNumericNode(nextToken);
				break;

			case JSON::TokenType::ObjectStart:
				table[key] = CreateJSONObjectNode(tokens);
				break;
			case JSON::TokenType::ListStart:
				table[key] = CreateJSONListNode(tokens);
				break;
		}

		nextToken = GetNextToken(tokens, { JSON::TokenType::Comma, JSON::TokenType::ObjectEnd });
		if (nextToken.Type == JSON::TokenType::ObjectEnd)
			break;
	}

	return std::make_shared<JSONObjectNode>(table);
}

JSONNode::Ptr JSONParser::CreateJSONStringNode(JSON::Token& token)
{
	return std::make_shared<JSONStringNode>(token.Value);
}

JSONNode::Ptr JSONParser::CreateJSONBoolNode(JSON::Token& token)
{
	return std::make_shared<JSONBoolNode>(token.Value == "true" ? true : false);
}

JSONNode::Ptr JSONParser::CreateJSONNumericNode(JSON::Token& token)
{
	float value = std::stof(token.Value);

	if (std::ceil(value) == value)
		return CreateJSONIntegerNode(token);
	else
		return CreateJSONFloatNode(token);
}

JSONNode::Ptr JSONParser::CreateJSONIntegerNode(JSON::Token& token)
{
	return std::make_shared<JSONIntegerNode>(std::stoi(token.Value));
}

JSONNode::Ptr JSONParser::CreateJSONFloatNode(JSON::Token& token)
{
	return std::make_shared<JSONFloatNode>(std::stof(token.Value));
}

JSONNode::Ptr JSONParser::CreateJSONListNode(std::queue<JSON::Token>& tokens)
{
	JSON::Token nextToken = PeekNextToken(tokens, { JSON::TokenType::Bool, JSON::TokenType::Number, JSON::TokenType::String, JSON::TokenType::ListEnd });
	JSON::TokenType expectedType = nextToken.Type;

	JSONNode::Ptr result;
	switch (expectedType)
	{
		case JSON::TokenType::String:
			result = CreateJSONListNode<std::string>(tokens, expectedType, [](std::string s) { return s; });
			break;
		case JSON::TokenType::Bool:
			result = CreateJSONListNode<bool>(tokens, expectedType, [](std::string s) { return s == "true"; });
			break;
		case JSON::TokenType::Number:
		{
			float value = std::stof(nextToken.Value);

			if (std::ceil(value) == value)
				result = CreateJSONListNode<int>(tokens, expectedType, [](std::string s) { return std::stoi(s); });
			else
				result = CreateJSONListNode<float>(tokens, expectedType, [](std::string s) { return std::stof(s); });

			break;
		}
		default:
			GetNextToken(tokens, { JSON::TokenType::ListEnd });
	}

	return result;
}


