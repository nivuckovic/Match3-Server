#pragma once
#include "BaseController.h"
#include "MatchState.h"
#include "Request.h"
#include "Response.h"

class MatchController : public BaseController
{
public:
	MatchController(GameController& gameController);

	void Begin() override;
	void End() override;

	void CreateNewMatch();
	Response OnUserTileMove(Request request);
	Response OnGenerateNewTiles(Request request);
	Response OnEndTurn(Request request);
};

