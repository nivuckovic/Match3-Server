#pragma once
enum class ResponseType
{
	AddedToQueue = 1,
	NewGameStart = 2,
	RemovedFromQueue = 3,
	NewConnection = 4,
	OpponentMoveTile = 5,
	OnTileMoveResponse = 6,
	GenerateNewTilesResponse = 7,
	NewTilesGenerated = 8,
	OpponentEndTurn = 9,
	EndTurnResponse = 10,
};

