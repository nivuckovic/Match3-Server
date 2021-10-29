#pragma once

#include <boost/asio.hpp>
#include "TCPConnection.h"
#include "Response.h"
#include <map>
#include "GameController.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class TCPServer
{
public:
	TCPServer(io_service& ioService);
	~TCPServer();

	void Run();
	void Update();
	void UpdateConnections();

	GameController::Ptr GetGameController(std::string guid);

	void HandleQueuedResponses();

	static char DELIMITER;

	static std::string CreateUUID();
private:

	void StartAccept();
	void HandleAccept(TCPConnection::Pointer newConnection, const boost::system::error_code& error);

	io_service& _ioService;
	tcp::acceptor _acceptor;

	boost::asio::deadline_timer _updateTimer;
	
	std::map<std::string, GameController::Ptr> _connections;
	
};

