#pragma once

#include "BaseController.h"
#include <memory>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class ConnectionController : public BaseController
{
public:
	typedef std::unique_ptr<ConnectionController> Ptr;
	// ConnectionController(GameController& gameController, TCPServer& tcpServer, TCPConnection* tcpConnection);
	ConnectionController(GameController& gameController, TCPServer& tcpServer, std::shared_ptr<TCPConnection> tcpConnection, std::string guid);

	void Begin() override;
	void End() override;

	bool IsOpen();
	void Close();

	std::string GetConnectionUUID();

	std::shared_ptr<GameController> GetGameController(std::string guid);
	std::shared_ptr<GameController> GetGameController();

	void SendResponse(Response Response);
	void HandleQueuedResponses();
	void HandleDisconnect();

private:
	TCPServer& _tcpServer;
	std::shared_ptr<TCPConnection> _tcpConnection;

	std::string _guid;
};

