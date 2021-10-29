#pragma once

namespace JSON
{
	enum class TokenType
	{
		ObjectStart, // 0
		ObjectEnd, // 1
		String, // 2
		Number, // 3
		Key, // 4
		Colon, // 5
		Comma, // 6
		Bool, // 7
		Invalid,
		ListStart,
		ListEnd
	};

	static std::string TypeToString(TokenType type)
	{
		std::string result;

		switch (type)
		{
			case TokenType::ObjectStart:
				result = "ObjectStart";
				break;
			case TokenType::ObjectEnd:
				result = "ObjectEnd";
				break;
			case TokenType::String:
				result = "String";
				break;
			case TokenType::Number:
				result = "Number";
				break;
			case TokenType::Key:
				result = "Key";
				break;
			case TokenType::Colon:
				result = "Colon";
				break;
			case TokenType::Comma:
				result = "Comma";
				break;
			case TokenType::Bool:
				result = "Bool";
				break;
			case TokenType::Invalid:
				result = "Invalid";
				break;
			case TokenType::ListStart:
				result = "ListStart";
				break;
			case TokenType::ListEnd:
				result = "ListEnd";
				break;
		}

		return result;
	}

	struct Token
	{
		TokenType Type;
		std::string Value;

		Token(TokenType type, std::string value = "")
		{
			Type = type;
			Value = value;
		}
	};
}