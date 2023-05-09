#include "UpMoveCommand.h"
#include "Vector3.h"

void UpMoveCommand::Execute(Player* player)
{
	//ã•ûŒü‚Ö‚ÌˆÚ“®ƒxƒNƒgƒ‹
	const Vector3 moveVec = { 0.0f, 1.0f, 0.0f };
	player->AddPlayerVector(moveVec);
}
