#include "TCPServer.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Logger.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "ConnectionController.h"


using namespace std::placeholders;

char TCPServer::DELIMITER = static_cast<char>(158);

TCPServer::TCPServer(io_service& ioService) : 
	_ioService(ioService), 
	_acceptor(ioService, tcp::endpoint(tcp::v4(), 1234)), 
	_updateTimer(_ioService, boost::posix_time::millisec(33)) 
{

};

TCPServer::~TCPServer()
{
	for (std::pair<std::string, GameController::Ptr> connection : _connections)
	{
		connection.second->Connection->Close();
	}
}

void TCPServer::Run()
{
	Logger::Log("Server", "Server pokrenut!");
	StartAccept();

	// _updateTimer.async_wait(boost::bind(&TCPServer::Update, this));
}

void TCPServer::Update()
{
	_updateTimer.expires_at(_updateTimer.expires_at() + boost::posix_time::millisec(33));
	_updateTimer.async_wait(boost::bind(&TCPServer::Update, this));
}

void TCPServer::StartAccept()
{
	TCPConnection::Pointer newConnection = TCPConnection::Create(_ioService, *this);
	
	_acceptor.async_accept(newConnection->GetSocket(), boost::bind(&TCPServer::HandleAccept, this, newConnection, boost::asio::placeholders::error));
}

void TCPServer::HandleAccept(TCPConnection::Pointer newConnection, const boost::system::error_code& error)
{
	UpdateConnections();
	
	if (!error)
	{
		newConnection->SetName(_connections.size());
		newConnection->Start();

		Logger::Log("Prihvacena nova konekcija " + newConnection->GetName());
		
		std::string controllerGUID = CreateUUID();
		GameController::Ptr newController = std::make_shared<GameController>(controllerGUID, *this, newConnection);
		newConnection->SetGameController(newController);

		_connections[controllerGUID] = newController;

		JSONObjectNode::Ptr data = std::make_shared<JSONObjectNode>();
		data->AddValue("connectionName", controllerGUID);

		newController->Connection->SendResponse(Response::CreateResponse(ResponseType::NewConnection, "", data));
		HandleQueuedResponses();
	}

	StartAccept();
}


void TCPServer::UpdateConnections()
{
	for (auto it = _connections.begin(); it != _connections.end();)
	{
		if ((*it).second->Connection->IsOpen())
		{
			++it;
			continue;
		}

		it = _connections.erase(it);
	}
}


GameController::Ptr TCPServer::GetGameController(std::string guid)
{
	return _connections[guid];
}

void TCPServer::HandleQueuedResponses()
{
	for (auto it = _connections.begin(); it != _connections.end(); ++it)
	{
		if ((*it).second->Connection->IsOpen())
		{
			it->second->Connection->HandleQueuedResponses();
		}
	}
}

std::string TCPServer::CreateUUID()
{
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	return boost::lexical_cast<std::string>(uuid);
}