#pragma once
#include "BaseController.h"
#include <queue>
#include <string>
#include "Enums.h"

class MatchFinderController : public BaseController
{
public:
	MatchFinderController(GameController& gameController);

	void Begin() override;
	void End() override;

	Response AddToQueue(Request request);
	void StartNewMatch(std::string connection1, std::string connection2);

	void HandleDisconnect();
	
	Response OnQuitQueueRequest(Request request);

private:
	void SendStartNewMatchResponse(MatchTurn matchTurn);

	void RemovePlayerFromQueue();

private:
	static std::queue<std::string> _waitingPlayersQueue;
};

