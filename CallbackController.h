#pragma once

#include "BaseController.h"
#include <map>
#include "RequestType.h"
#include <functional>
#include "Response.h"
#include "Request.h"

class CallbackController : BaseController
{
public:
	CallbackController(GameController& gameController);

	void Begin() override;
	void End() override;

	void RegisterOnRequestCallbacks();

	Response InvokeCallback(Request& request);

private:
	std::map<RequestType, std::function<Response(Request)>> _onRequestCallbacks;
};

