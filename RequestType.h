#pragma once

enum class RequestType
{
	StartNewGame = 1,
	CancelStartNewGame = 2,
	TileMove = 3,
	GenerateNewTiles = 4,
	EndTurn = 5
};
