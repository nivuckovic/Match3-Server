#include "TCPConnection.h"

#include <boost/bind.hpp>
#include "Logger.h"
#include "TCPServer.h"
#include "JSONParser.h"
#include "StringUtility.h"
#include "CallbackController.h"
#include "ConnectionController.h"
#include "EnumConverter.h"

TCPConnection::TCPConnection(io_service& ioService, TCPServer& server) : _socket(ioService), _server(server)
{
	_isConnected = true;
};

tcp::socket& TCPConnection::GetSocket()
{
	return _socket;
}

std::string& TCPConnection::GetName()
{
	return _name;
}

void TCPConnection::QueueResponse(Response response)
{
	_queuedResponses.push(response);
}

void TCPConnection::SetName(int id)
{
	_name = "Connection_" + std::to_string(id);
	_id = id;
}

void TCPConnection::SetGameController(GameController::Ptr gameController)
{
	_gameController = gameController;
}

void TCPConnection::SendMessage(std::string message)
{
	// QUICK GET RESPONSE ID 

	std::string target = "\"responseType\" : ";
	int location = message.find(target);

	std::string substr = message.substr(location + target.size(), 3);
	std::string number = "";

	for (char c : substr)
	{
		if (isalnum(c))
			number += c;
	}

	int id = std::stoi(number);

	std::string responseName = EnumConverter<ResponseType>::EnumToString(static_cast<ResponseType>(id));

	// ...

	std::string log = "Response(" + responseName + "): " + message;
	Logger::LogColor(GetName(), log, _id + 1);

	boost::asio::write(_socket, boost::asio::buffer(message));

	Sleep(25);
}

std::shared_ptr<GameController> TCPConnection::GetGameController()
{
	return _gameController;
}

void TCPConnection::Start()
{
	// Logger::Log(GetName(), "Iniciram prihvacanje poruke!");

	_socket.async_receive(boost::asio::buffer(_buffer), 0,
		boost::bind(&TCPConnection::HandleMessage, this, 
			_error,
			boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::HandleMessage(const boost::system::error_code& error, std::size_t bytesTransfered)
{
	if (bytesTransfered == 0)
	{
		HandleDisconnect();
		return;
	}
	else 
	{
		std::string receivedMessage(_buffer.begin(), _buffer.begin() + bytesTransfered);
		// Logger::Log(GetName(), receivedMessage);

		std::vector<std::string> messages = StringUtility::Split(receivedMessage, TCPServer::DELIMITER);

		for (std::string& message : messages)
		{
			JSONObjectNode::Ptr requestNode = JSONParser::GetInstance().Decode(message);

			std::string requestName = EnumConverter<RequestType>::EnumToString(static_cast<RequestType>(requestNode->GetValue<int>("requestType")));
			std::string log = "Requst(" + requestName + "): " + message;
			Logger::LogColor(GetName(), log, _id + 1);

			Request request;
			request.Decode(requestNode);

			HandleRequest(request);
			_server.HandleQueuedResponses();
		}
	}

	Start();
}

void TCPConnection::HandleRequest(Request request)
{
	// std::string msg = _onRequestCallbacks[request.Type](request).Encode();

	// Logger::Log("HandleRequest", msg);

	std::string responseMessage = _gameController->Callbacks->InvokeCallback(request).Encode()->ToString();
	SendMessage(responseMessage);
}

void TCPConnection::HandleDisconnect()
{
	std::string message = "Disconnect";
	Logger::LogColor(GetName(), message, _id + 1);

	_gameController->Connection->HandleDisconnect();

	_socket.close();
}

/*
void TCPConnection::OnMessageSent(const boost::system::error_code& error, size_t bytes_transferred)
{
	
}
*/

void TCPConnection::OnMessageSent(std::shared_ptr<std::string> messagePtr, const boost::system::error_code& error)
{
	std::string log = "Response: " + *messagePtr;
	Logger::LogColor(GetName(), log, _id + 1);
}


void TCPConnection::HandleQueuedResponses()
{
	std::string finalMessage;

	while (!_queuedResponses.empty())
	{
		std::string msg = _queuedResponses.front().Encode()->ToString();
		_queuedResponses.pop();

		finalMessage += msg + TCPServer::DELIMITER;
	}

	if(finalMessage.length() > 0)
		SendMessage(finalMessage);
}

