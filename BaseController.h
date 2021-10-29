#pragma once

#include "Request.h"
#include "Response.h"

class GameController;

class TCPServer;
class TCPConnection;

class BaseController
{
public:
	BaseController(GameController& gameController) : _gameController(gameController) {};

	virtual void Begin() = 0;
	virtual void End() = 0;

protected:
	GameController& _gameController;
};

