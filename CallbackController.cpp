#include "CallbackController.h"

#include "MatchFinderController.h"
#include "GameController.h"
#include "MatchController.h"

CallbackController::CallbackController(GameController& gameController) : BaseController(gameController)
{

}

void CallbackController::Begin()
{
	RegisterOnRequestCallbacks();
}

void CallbackController::End()
{
	
}

void CallbackController::RegisterOnRequestCallbacks()
{
	_onRequestCallbacks[RequestType::StartNewGame] = std::bind(&MatchFinderController::AddToQueue, _gameController.MatchFinder.get(), std::placeholders::_1);
	_onRequestCallbacks[RequestType::CancelStartNewGame] = std::bind(&MatchFinderController::OnQuitQueueRequest, _gameController.MatchFinder.get(), std::placeholders::_1);
	_onRequestCallbacks[RequestType::TileMove] = std::bind(&MatchController::OnUserTileMove, _gameController.Match.get(), std::placeholders::_1);
	_onRequestCallbacks[RequestType::GenerateNewTiles] = std::bind(&MatchController::OnGenerateNewTiles, _gameController.Match.get(), std::placeholders::_1);
	_onRequestCallbacks[RequestType::EndTurn] = std::bind(&MatchController::OnEndTurn, _gameController.Match.get(), std::placeholders::_1);
}

Response CallbackController::InvokeCallback(Request& request)
{
	return _onRequestCallbacks[request.Type](request);
}
