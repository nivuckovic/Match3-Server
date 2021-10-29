#pragma once

#include <memory>
#include <array>
#include "IEncodable.h"
#include "Enums.h"

class GameController;

class MatchConnectionData : IEncodable
{
public:

	MatchConnectionData(std::shared_ptr<GameController> controller1, std::shared_ptr<GameController> controller2)
	{
		Player = controller1;
		Opponent = controller2;
	}

	std::shared_ptr<GameController> Player;
	std::shared_ptr<GameController> Opponent;

	JSONNode::Ptr Encode() override;

};

class MatchState : IEncodable
{
public:
	MatchState() {};

	JSONNode::Ptr Encode() override;

public:
	std::array<std::array<int, 10>, 10> Board;
	MatchTurn CurrentTurn;
};

