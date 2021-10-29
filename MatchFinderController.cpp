#include "MatchFinderController.h"

#include "GameController.h"
#include "ConnectionController.h"
#include "MatchState.h"
#include "MatchController.h"

std::queue<std::string> MatchFinderController::_waitingPlayersQueue;

MatchFinderController::MatchFinderController(GameController& gameController) : BaseController(gameController)
{

}

void MatchFinderController::Begin()
{

}

void MatchFinderController::End()
{

}

Response MatchFinderController::AddToQueue(Request request)
{
	_waitingPlayersQueue.push(_gameController.Connection->GetConnectionUUID());

	if (_waitingPlayersQueue.size() >= 2)
	{
		std::string connection1 = _waitingPlayersQueue.front();
		_waitingPlayersQueue.pop();

		std::string connection2 = _waitingPlayersQueue.front();
		_waitingPlayersQueue.pop();

		StartNewMatch(connection1, connection2);
	}

	return Response::CreateResponse(ResponseType::AddedToQueue, request.Identifier, std::make_shared<JSONObjectNode>());
}

void MatchFinderController::StartNewMatch(std::string connection1, std::string connection2)
{
	GameController::Ptr controller1 = _gameController.Connection->GetGameController(connection1);
	GameController::Ptr controller2 = _gameController.GetGameController();

	std::shared_ptr<MatchState> match = std::make_shared<MatchState>();

	controller1->MatchState = match;
	controller2->MatchState = match;
	
	controller1->MatchConnectionData = std::make_shared<MatchConnectionData>(controller1, controller2);
	controller2->MatchConnectionData = std::make_shared<MatchConnectionData>(controller2, controller1);

	_gameController.Match->CreateNewMatch();

	controller1->MatchFinder->SendStartNewMatchResponse(MatchTurn::Controller1);
	SendStartNewMatchResponse(MatchTurn::Controller2);
}

void MatchFinderController::HandleDisconnect()
{
	RemovePlayerFromQueue();
}

Response MatchFinderController::OnQuitQueueRequest(Request request)
{
	RemovePlayerFromQueue();

	return Response::CreateResponse(ResponseType::RemovedFromQueue, request.Identifier, std::make_shared<JSONObjectNode>());
}

void MatchFinderController::SendStartNewMatchResponse(MatchTurn matchTurn)
{
	JSONObjectNode::Ptr data = std::make_shared<JSONObjectNode>();
	data->AddValue("match", _gameController.MatchState->Encode());
	data->AddValue("startingTurn", static_cast<int>(matchTurn));

	_gameController.Connection->SendResponse(Response::CreateResponse(ResponseType::NewGameStart, "", data));
}

void MatchFinderController::RemovePlayerFromQueue()
{
	std::queue<std::string> tempQueue;
	while (_waitingPlayersQueue.size() > 0)
	{
		std::string connectionGUID = _waitingPlayersQueue.front();
		_waitingPlayersQueue.pop();

		if (connectionGUID != _gameController.Connection->GetConnectionUUID())
		{
			tempQueue.push(connectionGUID);
		}
	}

	std::swap(tempQueue, _waitingPlayersQueue);
}

/*
void MatchFinderController::AddPlayerToQueue(std::string connectionName)
{
	_waitingPlayersQueue.push(connectionName);
	
	if (_waitingPlayersQueue.size() >= 2)
	{
		StartMatch();
	}
}

void MatchFinderController::StartMatch()
{
	std::string firstPlayer = _waitingPlayersQueue.front();
	_waitingPlayersQueue.pop();

	std::string secondPlayer = _waitingPlayersQueue.front();
	_waitingPlayersQueue.pop();


}
*/