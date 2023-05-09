#include "LeftMoveCommand.h"
#include "Vector3.h"

void LeftMoveCommand::Execute(Player* player)
{
	//¶•ûŒü‚Ö‚ÌˆÚ“®ƒxƒNƒgƒ‹
	const Vector3 moveVec = { -1.0f, 0.0f, 0.0f };
	player->AddPlayerVector(moveVec);
}
