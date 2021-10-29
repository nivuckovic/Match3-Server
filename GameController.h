#pragma once

#include <memory>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class TCPServer;
class TCPConnection;

class ConnectionController;
class MatchFinderController;
class CallbackController;
class MatchController;

class MatchState;
class MatchConnectionData;

class GameController
{
public:
	typedef std::shared_ptr<GameController> Ptr;

	// GameController(TCPServer& tcpServer, TCPConnection* tcpConnection);
	GameController(std::string guid, TCPServer& tcpServer, std::shared_ptr<TCPConnection> tcpConnection);

	void Begin();

	// Napravi da je ova klasa friend pripadnoj funkciji u connectioncontrolleru
	std::shared_ptr<GameController> GetGameController();

public:
	std::shared_ptr<ConnectionController> Connection;
	std::shared_ptr<MatchFinderController> MatchFinder;
	std::shared_ptr<CallbackController> Callbacks;
	std::shared_ptr<MatchController> Match;
protected:

public:
	std::shared_ptr<MatchState> MatchState;
	std::shared_ptr<MatchConnectionData> MatchConnectionData;
};

