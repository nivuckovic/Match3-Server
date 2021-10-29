#include "GameController.h"
#include "TCPConnection.h"

#include "ConnectionController.h"
#include "MatchFinderController.h"
#include "CallbackController.h"
#include "MatchController.h"

/*
GameController::GameController(TCPServer& tcpServer, TCPConnection* tcpConnection) 
{
	Connection = new ConnectionController(*this, tcpServer, tcpConnection);
}
*/

GameController::GameController(std::string guid, TCPServer& tcpServer, std::shared_ptr<TCPConnection> tcpConnection)
{
	Connection = std::make_shared<ConnectionController>(*this, tcpServer, tcpConnection, guid);
	MatchFinder = std::make_shared<MatchFinderController>(*this);
	Callbacks = std::make_shared<CallbackController>(*this);
	Match = std::make_shared<MatchController>(*this);

	Begin();
}

void GameController::Begin()
{
	Connection->Begin();
	MatchFinder->Begin();
	Callbacks->Begin();
	Match->Begin();
}

std::shared_ptr<GameController> GameController::GetGameController()
{
	return Connection->GetGameController();
}

