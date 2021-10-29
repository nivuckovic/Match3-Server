#include "ConnectionController.h"

#include "TCPServer.h"
#include "TCPConnection.h"

#include "MatchFinderController.h"

ConnectionController::ConnectionController(GameController& gameController, TCPServer& tcpServer, std::shared_ptr<TCPConnection> tcpConnection, std::string guid) : BaseController(gameController), _tcpServer(tcpServer), _guid(guid)
{
	_tcpConnection = tcpConnection;
}

/*
ConnectionController::ConnectionController(GameController& gameController, TCPServer& tcpServer, TCPConnection* tcpConnection) : BaseController(gameController), _tcpServer(tcpServer), _tcpConnection(tcpConnection)
{

}
*/

void ConnectionController::Begin()
{
	
}

void ConnectionController::End()
{
	
}

bool ConnectionController::IsOpen()
{
	return _tcpConnection->GetSocket().is_open();
}

void ConnectionController::Close()
{
	_tcpConnection->GetSocket().close();
}

std::string ConnectionController::GetConnectionUUID()
{
	return _guid;
}

std::shared_ptr<GameController> ConnectionController::GetGameController()
{
	return _tcpServer.GetGameController(_guid);
}

std::shared_ptr<GameController> ConnectionController::GetGameController(std::string guid)
{
	return _tcpServer.GetGameController(guid);
}

void ConnectionController::SendResponse(Response response)
{
	_tcpConnection->QueueResponse(response);
}

void ConnectionController::HandleQueuedResponses()
{
	_tcpConnection->HandleQueuedResponses();
}

void ConnectionController::HandleDisconnect()
{
	_gameController.MatchFinder->HandleDisconnect();
}
