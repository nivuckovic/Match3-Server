#pragma once

#include "EnumMap.h"

#include "RequestType.h"
#include <string>
#include <map>

template <typename TEnum>
class EnumConverter
{
public:
	static std::string EnumToString(TEnum e)
	{
		return _enumMap.EnumToString(e);
	}

	static TEnum StringToEnum(std::string s)
	{
		return _enumMap.StringToEnum(s);
	}

private:
	static EnumMap<TEnum> _enumMap;
};

template <typename TEnum>
EnumMap<TEnum> EnumConverter<TEnum>::_enumMap;