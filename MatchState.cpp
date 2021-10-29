#include "MatchState.h"

#include <vector>
#include "JSONObjectNode.h"
#include "GameController.h"
#include "ConnectionController.h"

JSONNode::Ptr MatchState::Encode()
{
	JSONObjectNode::Ptr node = std::make_shared<JSONObjectNode>();

	// node->AddValue<std::string>("player", Player->Connection->GetConnectionUUID());
	// node->AddValue<std::string>("opponent", Opponent->Connection->GetConnectionUUID());

	std::vector<int> board;

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			board.push_back(Board[i][j]);
		}
	}

	node->AddValue<std::vector<int>>("board", board);
	node->AddValue("turn", static_cast<int>(CurrentTurn));

	return node;
}

JSONNode::Ptr MatchConnectionData::Encode()
{
	JSONObjectNode::Ptr node;

	node->AddValue("player", Player->Connection->GetConnectionUUID());
	node->AddValue("opponent", Opponent->Connection->GetConnectionUUID());


	return node;
}
