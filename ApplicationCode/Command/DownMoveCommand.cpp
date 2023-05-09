#include "DownMoveCommand.h"
#include "Vector3.h"

void DownMoveCommand::Execute(Player* player)
{
	//‰º•ûŒü‚Ö‚ÌˆÚ“®ƒxƒNƒgƒ‹
	const Vector3 moveVec = { 0.0f, -1.0f, 0.0f };
	player->AddPlayerVector(moveVec);
}
