#include "MatchController.h"

#include <random>
#include <array>
#include <iostream>
#include "MatchState.h"

#include "GameController.h"
#include "ConnectionController.h"

MatchController::MatchController(GameController& gameController) : BaseController(gameController)
{

}

void MatchController::Begin()
{
	
}

void MatchController::End()
{
	
}

void MatchController::CreateNewMatch()
{
	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_int_distribution<int> distribution_1_5(1, 5);

	std::array<std::array<int, 10>, 10> board;

	for (int row = 0; row < 10; ++row)
	{
		for (int column = 0; column < 10; ++column)
		{
			int newPiece = distribution_1_5(random_engine);
			int upPiece = 0, leftPiece = 0;

			// Provjera gore
			if (row >= 2 && board[row - 1][column] == newPiece && board[row - 2][column] == newPiece)
			{
				upPiece = newPiece;
			}

			// Provjera lijevo
			if (column >= 2 && board[row][column - 1] == newPiece && board[row][column - 2] == newPiece)
			{
				leftPiece = newPiece;
			}

			// Ima match
			while (newPiece == upPiece || newPiece == leftPiece)
			{
				newPiece = distribution_1_5(random_engine);
			}

			board[row][column] = newPiece;
		}
	}

	/*
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			std::cout << board[i][j] << ", ";
		}
		std::cout << std::endl;
	}
	*/


	_gameController.MatchState->Board = board;
	_gameController.MatchState->CurrentTurn = MatchTurn::Controller1;
}

Response MatchController::OnUserTileMove(Request request)
{
	Response response = Response::CreateResponse(ResponseType::OnTileMoveResponse, request.Identifier, std::make_shared<JSONObjectNode>());

	JSONObjectNode::Ptr data = std::make_shared <JSONObjectNode>();
	data->AddValue<int>("firstX", request.Data->GetValue<int>("firstX"));
	data->AddValue<int>("firstY", request.Data->GetValue<int>("firstY"));
	data->AddValue<int>("secondX", request.Data->GetValue<int>("secondX"));
	data->AddValue<int>("secondY", request.Data->GetValue<int>("secondY"));

	_gameController.MatchConnectionData->Opponent->Connection->SendResponse(Response::CreateResponse(ResponseType::OpponentMoveTile, "", data));

	return response;
}

Response MatchController::OnGenerateNewTiles(Request request)
{
	Response response = Response::CreateResponse(ResponseType::GenerateNewTilesResponse, request.Identifier, std::make_shared<JSONObjectNode>());

	std::vector<int> dropdownInfo = request.Data->GetValue <std::vector<int>>("dropdownInfo");

	std::random_device random_device;
	std::mt19937 random_engine(random_device());
	std::uniform_int_distribution<int> distribution_1_5(1, 5);

	std::vector<int> newTileTypes;
	for (int i = 0; i < dropdownInfo.size(); ++i)
	{
		for (int j = 0; j < dropdownInfo[i]; ++j)
		{
			newTileTypes.push_back(distribution_1_5(random_engine));
		}
	}

	response.Data->AddValue<std::vector<int>>("newTiles", newTileTypes);

	_gameController.MatchConnectionData->Opponent->Connection->SendResponse(Response::CreateResponse(ResponseType::NewTilesGenerated, "", response.Data));

	return response;
}

Response MatchController::OnEndTurn(Request request)
{
	if (_gameController.MatchState->CurrentTurn == MatchTurn::Controller1)
		_gameController.MatchState->CurrentTurn = MatchTurn::Controller2;
	else
		_gameController.MatchState->CurrentTurn = MatchTurn::Controller1;

	_gameController.MatchConnectionData->Opponent->Connection->SendResponse(Response::CreateResponse(ResponseType::OpponentEndTurn, "", std::make_shared<JSONObjectNode>()));

	return Response::CreateResponse(ResponseType::EndTurnResponse, request.Identifier, std::make_shared<JSONObjectNode>());
}
