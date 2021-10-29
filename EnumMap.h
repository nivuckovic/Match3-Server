#pragma once

#include <map>
#include <string>

#include "RequestType.h"
#include "ResponseType.h"

#include "Logger.h"

template <typename TEnum>
class EnumMapBase
{
public:

	std::string EnumToString(TEnum e)
	{
		std::string result = "";

		for (std::pair<const std::string, TEnum>& pair : _lookupTable)
		{
			if (pair.second == e)
			{
				result = pair.first;
				break;
			}
		}

		try
		{
			if(result == "")
				throw std::exception("Enum ne postoji!");
		}
		catch (std::exception& e)
		{
			Logger::Log(e.what());
		}

		return result;
	}

	TEnum StringToEnum(std::string s)
	{
		try
		{
			return _lookupTable[s];
		}
		catch (std::exception & e)
		{
			Logger::Log(e.what());
		}
	}

protected:
	std::map<std::string, TEnum> _lookupTable;
};

template <typename TEnum>
class EnumMap : EnumMapBase<TEnum>{};

// Request Type Enum
template<>
class EnumMap<RequestType> : public EnumMapBase<RequestType>
{
public:
	EnumMap()
	{
		_lookupTable = std::map<std::string, RequestType>({
			{ "StartNewGame", RequestType::StartNewGame},
			{ "CancelStartNewGame", RequestType::CancelStartNewGame},
			{ "GenerateNewTiles", RequestType::GenerateNewTiles},
			{ "TileMove", RequestType::TileMove},
			{ "EndTurn", RequestType::EndTurn}
		});
	}
};

// Response Type Enum
template<>
class EnumMap<ResponseType> : public EnumMapBase<ResponseType>
{
public:
	EnumMap()
	{
		_lookupTable = std::map<std::string, ResponseType>({
			{ "AddedToQueue", ResponseType::AddedToQueue},
			{ "NewGameStart", ResponseType::NewGameStart},
			{ "RemovedFromQueue", ResponseType::RemovedFromQueue},
			{ "OpponentMoveTile", ResponseType::OpponentMoveTile},
			{ "GenerateNewTilesResponse", ResponseType::GenerateNewTilesResponse},
			{ "NewConnection", ResponseType::NewConnection},
			{ "NewTilesGenerated", ResponseType::NewTilesGenerated},
			{ "OnTileMoveResponse", ResponseType::OnTileMoveResponse},
			{ "OpponentEndTurn", ResponseType::OpponentEndTurn},
			{ "EndTurnResponse", ResponseType::EndTurnResponse}

			});
	}
};
