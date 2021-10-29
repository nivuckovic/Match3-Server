#pragma once

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "Request.h"
#include "Response.h"
#include "GameController.h"
#include <queue>
#include <memory>

using namespace boost::asio;
using namespace boost::asio::ip;

class TCPServer;

class TCPConnection : public boost::enable_shared_from_this<TCPConnection>
{
public:
	typedef std::shared_ptr<TCPConnection> Pointer;

	static Pointer Create(io_service& ioService, TCPServer& server)
	{
		return Pointer(new TCPConnection(ioService, server));
	}

	tcp::socket& GetSocket();
	std::string& GetName();

	void QueueResponse(Response response);

	void Start();
	void SetName(int id);
	void SetGameController(GameController::Ptr gameController);

	void SendMessage(std::string message);

	std::shared_ptr<GameController> GetGameController();

	void HandleQueuedResponses();
private:
	TCPServer& _server;
	TCPConnection(io_service& ioService, TCPServer& server);

	void HandleMessage(const boost::system::error_code& error, std::size_t bytesTransfered);
	void HandleRequest(Request request);
	void HandleDisconnect();

	void OnMessageSent(std::shared_ptr<std::string> messagePtr, const boost::system::error_code& error);
	// void OnMessageSent(const boost::system::error_code& error, size_t bytes_transferred);

private:
	boost::array<char, 1024> _buffer;

	std::string _name;
	int _id;

	boost::system::error_code _error;
	tcp::socket _socket;
	
	bool _isConnected;

	GameController::Ptr _gameController;
	
	std::queue<Response> _queuedResponses;
};
